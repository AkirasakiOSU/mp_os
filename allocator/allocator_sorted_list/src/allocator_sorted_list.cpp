#include <not_implemented.h>

#include "../include/allocator_sorted_list.h"

#include <complex>

#include "../../allocator_boundary_tags/include/allocator_boundary_tags.h"

using bytePtr = unsigned char *;

constexpr size_t allocator_sorted_list::getGlobalMetaSize() {
    return sizeof(allocator *) + sizeof(logger *) + sizeof(std::mutex) + sizeof(void *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(size_t);
}

constexpr size_t allocator_sorted_list::getLocalMetaSize() {
    return sizeof(size_t) + sizeof(void *);
}

constexpr size_t allocator_sorted_list::getTrustedMemorySizeShift() {
    return 0;
}

constexpr size_t allocator_sorted_list::getAllocatorShift() {
    return getTrustedMemorySizeShift() + sizeof(size_t);
}

constexpr size_t allocator_sorted_list::getLoggerShift() {
    return getAllocatorShift() + sizeof(allocator *);
}

constexpr size_t allocator_sorted_list::getMutexShift() {
    return getLoggerShift() + sizeof(logger *);
}

constexpr size_t allocator_sorted_list::getFirstFreeMemoryShift() {
    return getMutexShift() + sizeof(std::mutex);
}

constexpr size_t allocator_sorted_list::getFitModeShift() {
    return getFirstFreeMemoryShift() + sizeof(std::mutex);
}

constexpr size_t allocator_sorted_list::getFirstByteOfTrustedMemory() {
    return getFitModeShift() + sizeof(allocator_with_fit_mode::fit_mode);
}

constexpr size_t allocator_sorted_list::getSizeOfBlockShift() {
    return sizeof(void *);
}

constexpr size_t allocator_sorted_list::getFirstByteOfBlock() {
    return getSizeOfBlockShift() + sizeof(size_t);
}

size_t allocator_sorted_list::getFreeMemorySize() const {
    size_t result = 0;
    if(_trusted_memory == nullptr) return result;
    void *pNow = *reinterpret_cast<void **>(reinterpret_cast<bytePtr>(_trusted_memory) + getFirstFreeMemoryShift());
    if(pNow == nullptr) return result;
    while(pNow != nullptr) {
        result += *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift());
        pNow = *reinterpret_cast<void **>(pNow);
    }
    return result;
}

void allocator_sorted_list::logBlockСondition(void *at) const {
    trace_with_guard("Вход в logBlockСondition");
    size_t sizeOfBlock = *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(at) + getSizeOfBlockShift());
    if(sizeOfBlock == getLocalMetaSize()) {
        debug_with_guard("Переданный блок пустой");
        return;
    }
    std::string result;
    at = reinterpret_cast<bytePtr>(at) + getFirstByteOfBlock();
    for(auto i = 0; i < sizeOfBlock - getLocalMetaSize(); ++i) {
        result += std::to_string(*(reinterpret_cast<bytePtr>(at) + i)) + " ";
    }
    debug_with_guard(result);
    trace_with_guard("Выход из logBlockСondition");
}

void allocator_sorted_list::logTrustedMemoryCondition() const {
    trace_with_guard("Вход в logTrustedMemoryCondition");
    if(_trusted_memory == nullptr) debug_with_guard("Аллокатор без памяти");
    auto res = get_blocks_info();
    std::string logStr = "\n";
    for(auto i : res) {
        logStr += (i.is_block_occupied) ? "occup" : "avail";
        logStr += " ";
        logStr += std::to_string(i.block_size - getLocalMetaSize()) + "\n";
    }
    debug_with_guard(logStr);
    trace_with_guard("Выход из logTrustedMemoryCondition");
}

void allocator_sorted_list::freeMemory() {
    if(_trusted_memory == nullptr) return;
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift()) -> ~mutex();
    auto allocatorPtr = *(reinterpret_cast<allocator **>(trusted_memory + getAllocatorShift()));
    if(allocatorPtr == nullptr) {
        ::operator delete(_trusted_memory);
    } else {
        allocatorPtr->deallocate(_trusted_memory);
    }
}

void *allocator_sorted_list::allocateFullBlock(void *pPrev, void *pNow) {
    trace_with_guard("Вход в allocateFullBlock");
    *(reinterpret_cast<void **>(pPrev)) = *(reinterpret_cast<void **>(pNow));
    *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
    trace_with_guard("Выход из allocateFullBlock");
    return reinterpret_cast<bytePtr>(pNow) + getFirstByteOfBlock();
}

void *allocator_sorted_list::allocateBlock(void *pPrev, void *pNow, size_t sizeOfNewBlock) {
    trace_with_guard("Вход в allocateBlock");
    auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift()));
    if(sizeOfBlock == sizeOfNewBlock) {
        return allocateFullBlock(pPrev, pNow);
    }
    if(sizeOfBlock > sizeOfNewBlock) {
        if(sizeOfBlock - sizeOfNewBlock < getLocalMetaSize()) {
            warning_with_guard(std::string("Выделено ") + std::to_string(sizeOfBlock) + std::string(" вместо ") + std::to_string(sizeOfNewBlock));
            return allocateFullBlock(pPrev, pNow);
        }
        void *newFreeBlock = reinterpret_cast<bytePtr>(pNow) + sizeOfNewBlock;
        *(reinterpret_cast<void **>(pPrev)) = newFreeBlock;
        *(reinterpret_cast<void **>(newFreeBlock)) = *(reinterpret_cast<void **>(pNow));
        *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(newFreeBlock) + getSizeOfBlockShift())) = sizeOfBlock - sizeOfNewBlock;
        *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
        *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift())) = sizeOfNewBlock;
        trace_with_guard("Выход из allocateBlock");
        return reinterpret_cast<bytePtr>(pNow) + getFirstByteOfBlock();
    }
    trace_with_guard("Выход из allocateBlock");
    throw std::bad_alloc();
}

void *allocator_sorted_list::allocateFirstFit(size_t size) {
    trace_with_guard("Вход в allocateFirstFit");
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    void *pPrev, *pNow;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    pPrev = trusted_memory + getFirstFreeMemoryShift();
    pNow = *reinterpret_cast<void **>(pPrev);
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock >= sizeOfNewBlock) {
            try {
                trace_with_guard("Выход из allocateFirstFit");
                return allocateBlock(pPrev, pNow, sizeOfNewBlock);
            }
            catch (std::bad_alloc const &e) {
                error_with_guard(e.what() + std::string(" in allocateFirstFit"));
                std::cerr << e.what() << std::endl;
                throw e;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    trace_with_guard("Выход из allocateFirstFit");
    throw std::bad_alloc();
}

void *allocator_sorted_list::allocateBestFit(size_t size) {
    trace_with_guard("Вход в allocateBestFit");
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    std::pair<void *, void *> bestBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    bestBlock.first = pPrev = trusted_memory + getFirstFreeMemoryShift();
    bestBlock.second = pNow = *reinterpret_cast<void **>(pPrev);
    if(pNow == nullptr) throw std::bad_alloc();
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock == sizeOfNewBlock) return allocateFullBlock(pPrev, pNow);
        if(sizeOfBlock > sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(bestBlock.second) + getSizeOfBlockShift())) > sizeOfBlock) {
                bestBlock.first = pPrev;
                bestBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        trace_with_guard("Выход из allocateBestFit");
        return allocateBlock(bestBlock.first, bestBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        trace_with_guard("Выход из allocateBestFit");
        error_with_guard(e.what() + std::string(" in allocateBestFit"));
        std::cerr << e.what() << std::endl;
        throw e;
    }
    throw std::bad_alloc();
    return nullptr;
}

void *allocator_sorted_list::allocateWorstFit(size_t size) {
    trace_with_guard("Вход в allocateWorstFit");
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    std::pair<void *, void *> worstBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    worstBlock.first = pPrev = trusted_memory + getFirstFreeMemoryShift();
    worstBlock.second = pNow = *reinterpret_cast<void **>(pPrev);
    if(pNow == nullptr) throw std::bad_alloc();
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock >= sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(worstBlock.second) + getSizeOfBlockShift())) < sizeOfBlock) {
                worstBlock.first = pPrev;
                worstBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        trace_with_guard("Выход из allocateWorstFit");
        return allocateBlock(worstBlock.first, worstBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        trace_with_guard("Выход из allocateWorstFit");
        log_with_guard(e.what() + std::string("AllocateWorstFit() allocator_sorted_list"), logger::severity::trace);
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

allocator_sorted_list::~allocator_sorted_list()
{
    freeMemory();
    //throw not_implemented("allocator_sorted_list::~allocator_sorted_list()", "your code should be here...");
}

allocator_sorted_list::allocator_sorted_list(
    allocator_sorted_list &&other) noexcept :
    _trusted_memory(nullptr)
{
    if(other._trusted_memory == nullptr) return;
    other.debug_with_guard("Вход в конструктор перемещения");
    reinterpret_cast<std::mutex *>(reinterpret_cast<bytePtr>(other._trusted_memory) + getMutexShift()) -> lock();
    _trusted_memory = other._trusted_memory;
    other._trusted_memory = nullptr;
    reinterpret_cast<std::mutex *>(reinterpret_cast<bytePtr>(other._trusted_memory) + getMutexShift()) -> unlock();
    debug_with_guard("Выход из конструктора перемещения");
    //throw not_implemented("allocator_sorted_list::allocator_sorted_list(allocator_sorted_list &&) noexcept", "your code should be here...");
}

allocator_sorted_list &allocator_sorted_list::operator=(
    allocator_sorted_list &&other) noexcept
{
    other.debug_with_guard("Вход в оператор перемещения");
    if(this != &other) {
        std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<bytePtr>(other._trusted_memory) + getMutexShift()));
        freeMemory();
        _trusted_memory = other._trusted_memory;
        other._trusted_memory = nullptr;
    }
    other.debug_with_guard("Выход из оператора перемещения");
    return *this;
    //throw not_implemented("allocator_sorted_list &allocator_sorted_list::operator=(allocator_sorted_list &&) noexcept", "your code should be here...");
}

allocator_sorted_list::allocator_sorted_list(
    size_t space_size,
    allocator *parent_allocator,
    logger *loger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode) :
    _trusted_memory(nullptr)
{
    if(!space_size) throw std::logic_error("Space_size cant be eq 0");
    try {
        auto fullSize = space_size + getGlobalMetaSize() + getLocalMetaSize();
        _trusted_memory = (parent_allocator == nullptr) ?
            ::operator new(fullSize) :
            parent_allocator->allocate(1, fullSize);
    }
    catch (std::bad_alloc const &e) {
        error_with_guard(e.what() + std::string(" in allocator_sorted_list()"));
        throw e;
    }
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    *(reinterpret_cast<size_t *>(trusted_memory + getTrustedMemorySizeShift())) = space_size + getGlobalMetaSize() + getLocalMetaSize();
    *(reinterpret_cast<allocator **>(trusted_memory + getAllocatorShift())) = parent_allocator;
    *(reinterpret_cast<logger **>(trusted_memory + getLoggerShift())) = loger;
    debug_with_guard(std::string("Вход в констректор, желаемый размер пространства: ") + std::to_string(space_size));
    new(reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift())) std::mutex();
    *(reinterpret_cast<void **>(trusted_memory + getFirstFreeMemoryShift())) = reinterpret_cast<void *>(trusted_memory + getFirstByteOfTrustedMemory());
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(trusted_memory + getFitModeShift())) = allocate_fit_mode;
    void *firstBlock = *(reinterpret_cast<void **>(trusted_memory + getFirstFreeMemoryShift()));
    *(reinterpret_cast<void **>(firstBlock)) = nullptr;
    *(reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(firstBlock) + getSizeOfBlockShift())) = space_size + getLocalMetaSize();
    debug_with_guard("Выход из конструктора");
    //throw not_implemented("allocator_sorted_list::allocator_sorted_list(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_sorted_list::allocate(
    size_t value_size,
    size_t values_count)
{
    debug_with_guard("Вход в allocate");
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    auto trusted_memory = reinterpret_cast<bytePtr>(_trusted_memory);
    auto mutex = reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift());
    std::lock_guard<std::mutex> locker(*mutex);
    auto blockSize = value_size * values_count;
    try {
        void *res = nullptr;
        auto fitMode = (reinterpret_cast<allocator_with_fit_mode::fit_mode *>(trusted_memory + getFitModeShift()));
        switch (static_cast<int>(*fitMode)) {
            case 0:
                res = allocateFirstFit(blockSize);
                debug_with_guard("Выход из allocate");
                logTrustedMemoryCondition();
                information_with_guard(std::string("Выполнено выделение памяти (firstFit), размер совбодной памяти состовляет ") + std::to_string(getFreeMemorySize()));
                return res;
            case 1:
                res = allocateBestFit(blockSize);
                debug_with_guard("Выход из allocate");
                logTrustedMemoryCondition();
                information_with_guard(std::string("Выполнено выделение памяти (bestFit), размер совбодной памяти состовляет ") + std::to_string(getFreeMemorySize()));
                return res;
            case 2:
                res = allocateWorstFit(blockSize);
                debug_with_guard("Выход из allocate");
                logTrustedMemoryCondition();
                information_with_guard(std::string("Выполнено выделение памяти (worstFit), размер совбодной памяти состовляет ") + std::to_string(getFreeMemorySize()));
                return res;
            default:
                throw std::bad_alloc();
        }
    }
    catch (std::bad_alloc const &e) {
        debug_with_guard("Выход из allocate");
        error_with_guard(e.what() + std::string(" in allocate"));
        throw e;
    }
    //throw not_implemented("[[nodiscard]] void *allocator_sorted_list::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_sorted_list::deallocate(
    void *at){
    debug_with_guard("Вход в deallocate");
    if(_trusted_memory == nullptr) throw std::logic_error("Allocator is empty");
    if(at == nullptr) return;
    if(at < reinterpret_cast<bytePtr>(_trusted_memory) + getGlobalMetaSize() ||
        at > reinterpret_cast<bytePtr>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(_trusted_memory) + getTrustedMemorySizeShift()))
        throw std::logic_error("Ptr is not contained in trusted memory");
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<bytePtr>(_trusted_memory) + getMutexShift()));
    at = reinterpret_cast<bytePtr>(at) - getFirstByteOfBlock();
    if(*reinterpret_cast<void **>(at) != _trusted_memory) throw std::logic_error("Pointer is not contained in that allocator");
    logBlockСondition(at);
    void **firstFreeBlock = reinterpret_cast<void **>(reinterpret_cast<bytePtr>(_trusted_memory) + getFirstFreeMemoryShift());
    // Если нет свободных блоков
    if(*firstFreeBlock == nullptr) {
        *firstFreeBlock = at;
        *reinterpret_cast<void **>(at) = nullptr;
        debug_with_guard("Выход из deallocate");
        logTrustedMemoryCondition();
        information_with_guard(std::string("Выполнено освобождение памяти, размер свободной памяти состовляет ") + std::to_string(getFreeMemorySize()));
        return;
    }
    void *pPrev = firstFreeBlock, *pNow = *firstFreeBlock;
    while(pNow != nullptr) {

        if(pPrev < at && pNow > at) {
            //Если нашли 2 блока между котороми находится занятый
            if(reinterpret_cast<bytePtr>(pPrev) + *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pPrev) + getSizeOfBlockShift()) == at) {
                //Если занятый стоит сразу за левым свободным
                //Добавляем к размеру предыдущего блока размер занятого -> объединаем их
                *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pPrev) + getSizeOfBlockShift()) += *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(at) + getSizeOfBlockShift());
                //начало занятого блока смещается в начало пердыдущего свободного
                at = pPrev;
            }else {
                //Если слева нет свободного блока
                //Левый будет указывать на занятый
                *reinterpret_cast<void **>(pPrev) = at;
            }
            if(reinterpret_cast<bytePtr>(at) + *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(at) + getSizeOfBlockShift()) == pNow) {
                //Если за занятым находится правый свободный
                //Если до этого было объединение с левым, то at = pPrev и произайдёт объединение с pPrev
                //Занятый указывает на тот блок, на который указывал правый
                *reinterpret_cast<void **>(at) = *reinterpret_cast<void **>(pNow);
                //К размеру занятого прибавляется размер правого -> происходит объединение
                *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(at) + getSizeOfBlockShift()) += *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift());
            }else {
                //Если за занятым не стоит свободный
                //Занятый будет указывать на правый свободный
                auto p = *reinterpret_cast<void **>(at);
                *reinterpret_cast<void **>(at) = pNow;
            }
            debug_with_guard("Выход из deallocate");
            logTrustedMemoryCondition();
            information_with_guard(std::string("Выполнено освобождение памяти, размер свободной памяти состовляет ") + std::to_string(getFreeMemorySize()));
            return;
        }
        pPrev = pNow;
        pNow = *reinterpret_cast<void **>(pNow);
    }
    //Получается наш новый блок будет в самом конце
    if(reinterpret_cast<bytePtr>(pPrev) + *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pPrev) + getSizeOfBlockShift()) == at) {
        //Занятый блок находится сразу за свободным
        //Прибавляем к размеру полседнего размер занятого -> объединяем их
        *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pPrev) + getSizeOfBlockShift()) += *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(at) + getSizeOfBlockShift());
    }else {
        //Занятый блок не находится сразу за свободным
        //Занятый будет указыватьв пустоту тк он теперь последний
        *reinterpret_cast<void **>(at) = nullptr;
        //Последний будет указывать на занятый
        *reinterpret_cast<void **>(pPrev) = at;
    }
    debug_with_guard("Выход из deallocate");
    logTrustedMemoryCondition();
    information_with_guard(std::string("Выполнено освобождение памяти, размер свободной памяти состовляет ") + std::to_string(getFreeMemorySize()));
    //Вроде всё 0_0
    //throw not_implemented("void allocator_sorted_list::deallocate(void *)", "your code should be here...");
}

inline void allocator_sorted_list::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    debug_with_guard("Вход в set_fit_mode");
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<bytePtr>(_trusted_memory) + getMutexShift()));
    if(_trusted_memory == nullptr) throw std::logic_error("Allocator is empty");
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<bytePtr>(_trusted_memory) + getFitModeShift())) = mode;
    debug_with_guard("Выход из set_fit_mode");
    //throw not_implemented("inline void allocator_sorted_list::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_sorted_list::get_allocator() const
{
    debug_with_guard("Вход в get_allocator");
    debug_with_guard("Выход из get_allocator");
    if(_trusted_memory == nullptr) return nullptr;
    return *(reinterpret_cast<allocator **>(reinterpret_cast<bytePtr>(_trusted_memory) + getAllocatorShift()));
    //throw not_implemented("inline allocator *allocator_sorted_list::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept
{
    debug_with_guard("Вход в get_info_blocks");
    std::vector<allocator_test_utils::block_info> res;
    size_t sizeOfTrustedMemory = *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(_trusted_memory) + getTrustedMemorySizeShift());
    void *pNow = reinterpret_cast<bytePtr>(_trusted_memory) + getFirstByteOfTrustedMemory(), *pLast = reinterpret_cast<bytePtr>(_trusted_memory) + sizeOfTrustedMemory;
    while(pNow < pLast) {
        auto blockSize = *reinterpret_cast<size_t *>(reinterpret_cast<bytePtr>(pNow) + getSizeOfBlockShift());
        res.emplace_back(blockSize, (*reinterpret_cast<void **>(pNow) == _trusted_memory));
        pNow = reinterpret_cast<bytePtr>(pNow) + blockSize;
    }
    debug_with_guard("Выход из get_info_block");
    return res;
    //throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_sorted_list::get_logger() const
{
    if(_trusted_memory == nullptr) return nullptr;
    return *(reinterpret_cast<logger **>(reinterpret_cast<bytePtr>(_trusted_memory) + getLoggerShift()));
    //throw not_implemented("inline logger *allocator_sorted_list::get_logger() const", "your code should be here...");
}

inline std::string allocator_sorted_list::get_typename() const noexcept
{
    return "allocator_sorted_list";
    //throw not_implemented("inline std::string allocator_sorted_list::get_typename() const noexcept", "your code should be here...");
}