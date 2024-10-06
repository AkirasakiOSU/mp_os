#include <not_implemented.h>

#include "../include/allocator_sorted_list.h"

#include <complex>


constexpr size_t allocator_sorted_list::getGlobalMetaSize() {
    return sizeof(allocator *) + sizeof(logger *) + sizeof(std::mutex *) + sizeof(void *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(size_t);
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
    return getFirstFreeMemoryShift() + sizeof(void *);
}

constexpr size_t allocator_sorted_list::getSizeOfBlockShift() {
    return sizeof(void *);
}

void allocator_sorted_list::freeMemory() {
    log_with_guard("freeMemory() allocator_sorted_list", logger::severity::trace);
    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);
    reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift()) -> ~mutex();
    auto allocatorPtr = *(reinterpret_cast<allocator **>(trusted_memory + getLoggerShift()));
    if(allocatorPtr == nullptr) {
        ::operator delete(_trusted_memory);
    } else {
        allocatorPtr->deallocate(_trusted_memory);
    }
    log_with_guard("~freeMemory() allocator_sorted_list", logger::severity::trace);
}

void *allocator_sorted_list::allocateFullBlock(void *pPrev, void *pNow) {
    log_with_guard("AllocateFullBlock() allocator_sorted_list", logger::severity::trace);
    *(reinterpret_cast<void **>(pPrev)) = *(reinterpret_cast<void **>(pNow));
    *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
    log_with_guard("~AllocateFullBlock() allocator_sorted_list", logger::severity::trace);
    return reinterpret_cast<unsigned char *>(pNow) + getLocalMetaSize();
}

void *allocator_sorted_list::allocateBlock(void *pPrev, void *pNow, size_t sizeOfNewBlock) {
    log_with_guard("AllocateBlock() allocator_sorted_list", logger::severity::trace);
    auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift()));
    if(sizeOfBlock == sizeOfNewBlock) {
        log_with_guard("~AllocateBlock() allocator_sorted_list", logger::severity::trace);
        return allocateFullBlock(pPrev, pNow);
    }
    if(sizeOfBlock > sizeOfNewBlock) {
        if(sizeOfBlock - sizeOfNewBlock < getLocalMetaSize()) {
            return allocateFullBlock(pPrev, pNow);
        }
        void *newFreeBlock = nullptr;
        *(reinterpret_cast<void **>(pPrev)) = newFreeBlock = reinterpret_cast<unsigned char *>(pNow) + sizeOfNewBlock;
        *(reinterpret_cast<void **>(newFreeBlock)) = *(reinterpret_cast<void **>(pNow));
        *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(newFreeBlock) + getSizeOfBlockShift())) = sizeOfBlock - sizeOfNewBlock;
        *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
        *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift())) = sizeOfNewBlock;
        log_with_guard("~AllocateBlock() allocator_sorted_list", logger::severity::trace);
        return reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(pNow) + getLocalMetaSize());
    }
    throw std::bad_alloc();
}

void *allocator_sorted_list::allocateFirstFit(size_t size) {
    log_with_guard("AllocateFirstFit() allocator_sorted_list", logger::severity::trace);
    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);
    void *pPrev, *pNow;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    pNow = *(reinterpret_cast<void **>(pPrev = reinterpret_cast<void *>(trusted_memory + getFirstFreeMemoryShift())));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock >= sizeOfNewBlock) {
            log_with_guard("~AllocateFirstFit() allocator_sorted_list", logger::severity::trace);
            return allocateBlock(pPrev, pNow, sizeOfNewBlock);
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    throw std::bad_alloc();
}

void *allocator_sorted_list::allocateBestFit(size_t size) {
    log_with_guard("AllocateBestFit() allocator_sorted_list", logger::severity::trace);
    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);
    std::pair<void *, void *> bestBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    bestBlock.second = pNow = *(reinterpret_cast<void **>(bestBlock.first = pPrev = reinterpret_cast<void *>(trusted_memory + getFirstFreeMemoryShift())));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock == sizeOfNewBlock) return allocateFullBlock(pPrev, pNow);
        if(sizeOfBlock > sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(bestBlock.second) + getSizeOfBlockShift())) > sizeOfBlock) {
                bestBlock.first = pPrev;
                bestBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        log_with_guard("~AllocateBestFit() allocator_sorted_list", logger::severity::trace);
        return allocateBlock(bestBlock.first, bestBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        log_with_guard(e.what() + std::string("AllocateBestFit() allocator_sorted_list"), logger::severity::trace);
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        log_with_guard(e.what() + std::string("AllocateBestFit() allocator_sorted_list"), logger::severity::trace);
        std::cerr << e.what() << std::endl;
        throw e;
    }
    throw std::bad_alloc();
    return nullptr;
}

void *allocator_sorted_list::allocateWorstFit(size_t size) {
    log_with_guard("AllocateWorstFit() allocator_sorted_list", logger::severity::trace);
    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);
    std::pair<void *, void *> worstBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + getLocalMetaSize();
    worstBlock.second = pNow = *(reinterpret_cast<void **>(worstBlock.first = pPrev = reinterpret_cast<void *>(trusted_memory + getFirstFreeMemoryShift())));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift()));
        if(sizeOfBlock >= sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(worstBlock.second) + getSizeOfBlockShift())) < sizeOfBlock) {
                worstBlock.first = pPrev;
                worstBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        log_with_guard("~AllocateWorstFit() allocator_sorted_list", logger::severity::trace);
        return allocateBlock(worstBlock.first, worstBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        log_with_guard(e.what() + std::string("AllocateWorstFit() allocator_sorted_list"), logger::severity::trace);
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
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
    _trusted_memory(other._trusted_memory)
{
    other._trusted_memory = nullptr;
    //throw not_implemented("allocator_sorted_list::allocator_sorted_list(allocator_sorted_list &&) noexcept", "your code should be here...");
}

allocator_sorted_list &allocator_sorted_list::operator=(
    allocator_sorted_list &&other) noexcept
{
    if(this != &other) {
        freeMemory();
        _trusted_memory = other._trusted_memory;
        other._trusted_memory = nullptr;
    }
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
        auto fullSize = space_size + getGlobalMetaSize();
        if(parent_allocator == nullptr) _trusted_memory = ::operator new(fullSize);
        else _trusted_memory = parent_allocator->allocate(fullSize, 1);
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() <<std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() <<std::endl;
        throw e;
    }
    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);

    *(reinterpret_cast<size_t *>(trusted_memory + getTrustedMemorySizeShift())) = space_size;
    *(reinterpret_cast<allocator **>(trusted_memory + getAllocatorShift())) = parent_allocator;
    *(reinterpret_cast<logger **>(trusted_memory + getLoggerShift())) = loger;
    new(reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift())) std::mutex();
    *(reinterpret_cast<void **>(trusted_memory + getFirstFreeMemoryShift())) = reinterpret_cast<void *>(trusted_memory + getGlobalMetaSize());
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(trusted_memory + getFitModeShift())) = allocate_fit_mode;

    void *firstBlock = *(reinterpret_cast<void **>(trusted_memory + getFirstFreeMemoryShift()));
    *(reinterpret_cast<void **>(firstBlock)) = nullptr;
    *(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(firstBlock) + getSizeOfBlockShift())) = space_size + getLocalMetaSize();
    //throw not_implemented("allocator_sorted_list::allocator_sorted_list(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_sorted_list::allocate(
    size_t value_size,
    size_t values_count)
{
    log_with_guard("allocate() allocator_sorted_list", logger::severity::trace);

    auto trusted_memory = reinterpret_cast<unsigned char *>(_trusted_memory);
    auto mutex = reinterpret_cast<std::mutex *>(trusted_memory + getMutexShift());
    mutex->lock();
    auto blockSize = value_size * values_count;
    try {
        void *res = nullptr;
        switch (static_cast<int>(*(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(trusted_memory + getFitModeShift())))) {
            case 0:
                res = allocateFirstFit(blockSize);
                mutex->unlock();
                log_with_guard("~allocate() allocator_sorted_list", logger::severity::trace);
                return res;
            case 1:
                res = allocateBestFit(blockSize);
                mutex->unlock();
                log_with_guard("~allocate() allocator_sorted_list", logger::severity::trace);
                return res;
            case 2:
                res = allocateWorstFit(blockSize);
                mutex->unlock();
                log_with_guard("~allocate() allocator_sorted_list", logger::severity::trace);
                return res;
            default:
                throw std::bad_alloc();
        }
    }
    catch (std::bad_alloc const &e) {
        mutex->unlock();
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        mutex->unlock();
        std::cerr << e.what() << std::endl;
        throw e;
    }

    mutex->unlock();
    //throw not_implemented("[[nodiscard]] void *allocator_sorted_list::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_sorted_list::deallocate(
    void *at){
    log_with_guard("deallocate() allocator_sorted_list", logger::severity::trace);
    at = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(at) - getLocalMetaSize());
    if(*reinterpret_cast<void **>(at) != _trusted_memory) throw std::logic_error("Pointer is not contained in that allocator");
    auto firstFreeBlock = reinterpret_cast<void **>(reinterpret_cast<unsigned int *>(_trusted_memory) + getFirstFreeMemoryShift());
    // Если нет свободных блоков
    if(*firstFreeBlock == nullptr) {
        *firstFreeBlock = at;
        *reinterpret_cast<void **>(at) = nullptr;
        log_with_guard("~deallocate() allocator_sorted_list", logger::severity::trace);
        return;
    }
    void *pPrev = firstFreeBlock, *pNow = *firstFreeBlock;
    while(*reinterpret_cast<void **>(pNow) != nullptr) {
        if(pPrev < at && pNow > at) {
            //Если нашли 2 блока между котороми находится занятый
            if(reinterpret_cast<unsigned char *>(pPrev) + *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pPrev) + getSizeOfBlockShift()) == at) {
                //Если занятый стоит сразу за левым свободным
                //Добавляем к размеру предыдущего блока размер занятого -> объединаем их
                *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pPrev) + getSizeOfBlockShift()) += *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(at) + getSizeOfBlockShift());
                //начало занятого блока смещается в начало пердыдущего свободного
                at = pPrev;
            }else {
                //Если слева нет свободного блока
                //Левый будет указывать на занятый
                *reinterpret_cast<void **>(pPrev) = at;
            }
            if(reinterpret_cast<unsigned char *>(at) + *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(at) + getSizeOfBlockShift()) == pNow) {
                //Если за занятым находится правый свободный
                //Если до этого было объединение с левым, то at = pPrev и произайдёт объединение с pPrev
                //Занятый указывает на тот блок, на который указывал правый
                *reinterpret_cast<void **>(at) = *reinterpret_cast<void **>(pNow);
                //К размеру занятого прибавляется размер правого -> происходит объединение
                *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(at) + getSizeOfBlockShift()) = *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pNow) + getSizeOfBlockShift());
            }else {
                //Если за занятым не стоит свободный
                //Занятый будет указывать на правый свободный
                *reinterpret_cast<void **>(at) = pNow;
            }
            log_with_guard("~allocate() allocator_sorted_list", logger::severity::trace);
            return;
        }
        pPrev = pNow;
        pNow = *reinterpret_cast<void **>(pNow);
    }
    //Получается наш новый блок будет в самом конце
    if(reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pPrev) + getSizeOfBlockShift()) == at) {
        //Занятый блок находится сразу за свободным
        //Прибавляем к размеру полседнего размер занятого -> объединяем их
        *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(pPrev) + getSizeOfBlockShift()) += *reinterpret_cast<size_t *>(reinterpret_cast<unsigned char *>(at) + getSizeOfBlockShift());
    }else {
        //Занятый блок не находится сразу за свободным
        //Занятый будет указыватьв пустоту тк он теперь последний
        *reinterpret_cast<void **>(at) = nullptr;
        //Последний будет указывать на занятый
        *reinterpret_cast<void **>(pPrev) = at;
    }
    log_with_guard("~deallocate() allocator_sorted_list", logger::severity::trace);
    //Вроде всё 0_0
    //throw not_implemented("void allocator_sorted_list::deallocate(void *)", "your code should be here...");
}

inline void allocator_sorted_list::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<unsigned char *>(_trusted_memory) + getFitModeShift())) = mode;
    //throw not_implemented("inline void allocator_sorted_list::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_sorted_list::get_allocator() const
{
    return *(reinterpret_cast<allocator **>(reinterpret_cast<unsigned char *>(_trusted_memory) + getAllocatorShift()));
    //throw not_implemented("inline allocator *allocator_sorted_list::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_sorted_list::get_logger() const
{
    return *(reinterpret_cast<logger **>(reinterpret_cast<unsigned char *>(_trusted_memory) + getLoggerShift()));
    //throw not_implemented("inline logger *allocator_sorted_list::get_logger() const", "your code should be here...");
}

inline std::string allocator_sorted_list::get_typename() const noexcept
{
    return "allocator_sorted_list";
    //throw not_implemented("inline std::string allocator_sorted_list::get_typename() const noexcept", "your code should be here...");
}