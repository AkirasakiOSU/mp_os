#include <not_implemented.h>

#include "../include/allocator_boundary_tags.h"

#include <mutex>

constexpr size_t allocator_boundary_tags::getGlobalMetaSize() {
    return sizeof(size_t) + sizeof(logger *) + sizeof(allocator *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(std::mutex);
}

constexpr size_t allocator_boundary_tags::getLocalMetaSize() {
    return sizeof(bool) + sizeof(size_t) + sizeof(void *);
}

constexpr size_t allocator_boundary_tags::getSizeOfTrustedMemoryShift() {
    return 0;
}

constexpr size_t allocator_boundary_tags::getLoggerShift() {
    return getSizeOfTrustedMemoryShift() + sizeof(size_t);
}

constexpr size_t allocator_boundary_tags::getAllocatorShift() {
    return getLoggerShift() + sizeof(logger *);
}

constexpr size_t allocator_boundary_tags::getFitModeShift() {
    return getAllocatorShift() + sizeof(allocator *);
}

constexpr size_t allocator_boundary_tags::getMutexShift() {
    return getFitModeShift() + sizeof(allocator_with_fit_mode::fit_mode);
}

constexpr size_t allocator_boundary_tags::getFirstBlockShift() {
    return getMutexShift() + sizeof(std::mutex);
}

constexpr size_t allocator_boundary_tags::getTrustedMemoryPtrShift() {
    return 0;
}

constexpr size_t allocator_boundary_tags::getStatusOfBlockShift() {
    return sizeof(void *);
}

constexpr size_t allocator_boundary_tags::getSizeOfBlockShift() {
    return getStatusOfBlockShift() + sizeof(bool);
}

void allocator_boundary_tags::initializationOfLocalMeta(byte *ptr, size_t sizeOfBlock, bool statusOfBlock) {
    *reinterpret_cast<void **>(ptr + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<bool *>(ptr + getStatusOfBlockShift()) = statusOfBlock;
    *reinterpret_cast<size_t *>(ptr + getSizeOfBlockShift()) = sizeOfBlock;
}

void allocator_boundary_tags::freeMemory() {
    if(_trusted_memory == nullptr) return;
    destruct(reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    if(get_allocator() == nullptr) ::operator delete(_trusted_memory);
    else get_allocator()->deallocate(_trusted_memory);
    _trusted_memory = nullptr;
}

void *allocator_boundary_tags::allocateFirstFit(size_t sizeOfNewBlock) {
    byte *curentBlock = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift(),
         *lastPtr = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    while(curentBlock < lastPtr) {
        auto sizeOfBlock = *reinterpret_cast<size_t *>(curentBlock + getSizeOfBlockShift());
        if(!*reinterpret_cast<bool *>(curentBlock + getStatusOfBlockShift())) {
            if(sizeOfBlock == sizeOfNewBlock) return allocateFullBlock(curentBlock);
            if(sizeOfBlock > sizeOfNewBlock) return allocateBlock(curentBlock, sizeOfNewBlock);
        }
        curentBlock += sizeOfBlock;
    }
    throw std::bad_alloc();
}

void *allocator_boundary_tags::allocateBestFit(size_t sizeOfBlock) {
    byte *bestBlock = findFirstFreeBlock(sizeOfBlock),
    *currentBlock = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift(),
    *pLast = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    if(bestBlock == nullptr) throw std::bad_alloc();
    if(*reinterpret_cast<size_t *>(bestBlock + getSizeOfBlockShift()) == sizeOfBlock) return allocateFullBlock(bestBlock);
    while(currentBlock < pLast) {
        if(!*reinterpret_cast<bool *>(currentBlock + getStatusOfBlockShift())) {
            if(*reinterpret_cast<size_t *>(bestBlock + getSizeOfBlockShift()) > *reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift())) bestBlock = currentBlock;
        }
        currentBlock += *reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift());
    }
    return allocateBlock(bestBlock, sizeOfBlock);
}

void *allocator_boundary_tags::allocateWorstFit(size_t sizeOfBlock) {
    byte *bestBlock = findFirstFreeBlock(sizeOfBlock),
    *currentBlock = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift(),
    *pLast = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    if(bestBlock == nullptr) throw std::bad_alloc();
    if(*reinterpret_cast<size_t *>(bestBlock + getSizeOfBlockShift()) == sizeOfBlock) return allocateFullBlock(bestBlock);
    while(currentBlock < pLast) {
        if(!*reinterpret_cast<bool *>(currentBlock + getStatusOfBlockShift())) {
            if(*reinterpret_cast<size_t *>(bestBlock + getSizeOfBlockShift()) < *reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift())) bestBlock = currentBlock;
        }
        currentBlock += *reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift());
    }
    return allocateBlock(bestBlock, sizeOfBlock);
}

void *allocator_boundary_tags::allocateBlock(void *block, size_t sizeOfNewBlock) {
    byte *pBlock = reinterpret_cast<byte *>(block);
    auto minSizeOfBlock = 2 * getLocalMetaSize(),
    sizeOfBlock = *reinterpret_cast<size_t *>(pBlock + getSizeOfBlockShift());
    if(sizeOfBlock - sizeOfNewBlock < minSizeOfBlock) return allocateFullBlock(block);
    *reinterpret_cast<void **>(pBlock + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<bool *>(pBlock + getStatusOfBlockShift()) = true;
    *reinterpret_cast<size_t *>(pBlock + getSizeOfBlockShift()) = sizeOfNewBlock;
    auto resultPtr = pBlock + getLocalMetaSize();
    pBlock += sizeOfNewBlock;
    *reinterpret_cast<void **>((pBlock - getLocalMetaSize()) + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<bool *>((pBlock - getLocalMetaSize()) + getStatusOfBlockShift()) = true;
    *reinterpret_cast<size_t *>((pBlock - getLocalMetaSize()) + getSizeOfBlockShift()) = sizeOfNewBlock;

    *reinterpret_cast<void **>(pBlock + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<bool *>(pBlock + getStatusOfBlockShift()) = false;
    *reinterpret_cast<size_t *>(pBlock + getSizeOfBlockShift()) = sizeOfBlock - sizeOfNewBlock;
    pBlock += sizeOfBlock - sizeOfNewBlock - getLocalMetaSize();
    *reinterpret_cast<void **>(pBlock + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<bool *>(pBlock + getStatusOfBlockShift()) = false;
    *reinterpret_cast<size_t *>(pBlock + getSizeOfBlockShift()) = sizeOfBlock - sizeOfNewBlock;
    return resultPtr;
}

void *allocator_boundary_tags::allocateFullBlock(void *block) {
    byte *pBlock = reinterpret_cast<byte *>(block);
    *reinterpret_cast<bool *>(pBlock + getStatusOfBlockShift()) = true;
    auto secondMeta = pBlock + *reinterpret_cast<size_t *>(pBlock + getSizeOfBlockShift()) - getLocalMetaSize();
    *reinterpret_cast<bool *>(secondMeta + getStatusOfBlockShift()) = true;
    *reinterpret_cast<void **>(pBlock + getTrustedMemoryPtrShift()) = _trusted_memory;
    *reinterpret_cast<void **>(secondMeta + getTrustedMemoryPtrShift()) = _trusted_memory;
    return pBlock + getLocalMetaSize();
}

byte *allocator_boundary_tags::findFirstFreeBlock(size_t sizeOfBlock) const {
    byte *currentBlock = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift(),
    *pLast = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    while(currentBlock < pLast) {
        if(!*reinterpret_cast<bool *>(currentBlock + getStatusOfBlockShift())) {
            if(*reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift()) >= sizeOfBlock) return currentBlock;
        }
        currentBlock += *reinterpret_cast<size_t *>(currentBlock + getSizeOfBlockShift());
    }
    return nullptr;
}

allocator_boundary_tags::~allocator_boundary_tags()
{
    freeMemory();
    //throw not_implemented("allocator_boundary_tags::~allocator_boundary_tags()", "your code should be here...");
}

allocator_boundary_tags::allocator_boundary_tags(
    allocator_boundary_tags &&other) noexcept :
    _trusted_memory(nullptr)
{
    if(other._trusted_memory == nullptr) return;
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(other._trusted_memory) + getMutexShift()));
    _trusted_memory = other._trusted_memory;
    other._trusted_memory = nullptr;
    //throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(allocator_boundary_tags &&) noexcept", "your code should be here...");
}

allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags &&other) noexcept
{
    if(this != &other) {
        std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(other._trusted_memory) + getMutexShift()));
        freeMemory();
        _trusted_memory = other._trusted_memory;
        other._trusted_memory = nullptr;
    }
    return *this;
    //throw not_implemented("allocator_boundary_tags &allocator_boundary_tags::operator=(allocator_boundary_tags &&) noexcept", "your code should be here...");
}

allocator_boundary_tags::allocator_boundary_tags(
    size_t space_size,
    allocator *parent_allocator,
    logger *logger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode) :
    _trusted_memory(nullptr)
{
    size_t fullSize = getGlobalMetaSize() + space_size + (2 * getLocalMetaSize());
    try {
        _trusted_memory = (parent_allocator == nullptr) ? ::operator new(fullSize) : parent_allocator->allocate(1, fullSize);
    }
    catch (std::bad_alloc const &e) {
        throw e;
    }
    byte *ptr = reinterpret_cast<byte *>(_trusted_memory);
    *reinterpret_cast<size_t *>(ptr + getSizeOfTrustedMemoryShift()) = fullSize;
    *reinterpret_cast<class logger **>(ptr + getLoggerShift()) = logger;
    *reinterpret_cast<allocator **>(ptr + getAllocatorShift()) = parent_allocator;
    *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(ptr + getFitModeShift()) = allocate_fit_mode;
    construct(reinterpret_cast<std::mutex *>(ptr + getMutexShift()));
    ptr += getFirstBlockShift();
    initializationOfLocalMeta(ptr, fullSize - getGlobalMetaSize(), false);
    ptr += space_size + getLocalMetaSize();
    initializationOfLocalMeta(ptr, fullSize - getGlobalMetaSize(), false);
    //throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_boundary_tags::allocate(
    size_t value_size,
    size_t values_count)
{
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    auto sizeOfNewBlock = (value_size * values_count) + (2 * getLocalMetaSize());
    auto fitMode = reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<byte *>(_trusted_memory) + getFitModeShift());
    void *res = nullptr;
    try {
        switch(static_cast<int>(*fitMode)) {
            case 0:
                res = allocateFirstFit(sizeOfNewBlock);
                break;
            case 1:
                res = allocateBestFit(sizeOfNewBlock);
                break;
            case 2:
                res = allocateWorstFit(sizeOfNewBlock);
                break;
            default:
                throw std::bad_alloc();
        }
    }
    catch (std::bad_alloc const &e) {
        error_with_guard(e.what());
        throw e;
    }
    return res;
    throw std::bad_alloc();
    //throw not_implemented("[[nodiscard]] void *allocator_boundary_tags::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_boundary_tags::deallocate(
    void *at)
{
    if(_trusted_memory == nullptr) throw std::logic_error("Allocator is empty");
    if(at == nullptr) return;
    if(at < reinterpret_cast<byte *>(_trusted_memory) + getGlobalMetaSize() ||
        at > reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift()))
        throw std::logic_error("Pointer is not contained in trusted memory");
    at = reinterpret_cast<byte *>(at) - getLocalMetaSize();
    if(*reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getTrustedMemoryPtrShift()) != _trusted_memory) throw std::logic_error("Pointer is not contained in that allocator");
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    auto sizeOfAt = *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + getSizeOfBlockShift());
    if(!*reinterpret_cast<bool *>(reinterpret_cast<byte *>(at) - getLocalMetaSize() + getStatusOfBlockShift()) && at != reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift()) {
        //Перед новым стоит свободный
        //Взяли размер предыдущего
        auto sizeOfPrevBlock = *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) - getLocalMetaSize() + getSizeOfBlockShift());
        //Поставили at на предыдущий
        at = reinterpret_cast<byte *>(at) - sizeOfPrevBlock;
        //К размеру предыдщего добавили наш
        *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + getSizeOfBlockShift()) += sizeOfAt;
        sizeOfAt = *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + getSizeOfBlockShift());
        //Пометили нашу страую мету свободной
        *reinterpret_cast<bool *>(reinterpret_cast<byte *>(at) + sizeOfAt - getLocalMetaSize() + getStatusOfBlockShift()) = false;
        //Положили в старую мету новый размер
        *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + sizeOfAt - getLocalMetaSize() + getSizeOfBlockShift()) = sizeOfAt;
    } else {
        //Если справа нет свободного блока
        //Пометили обе меты свободными
        *reinterpret_cast<bool *>(reinterpret_cast<byte *>(at) + getStatusOfBlockShift()) = false;
        *reinterpret_cast<bool *>(reinterpret_cast<byte *>(at) + sizeOfAt - getLocalMetaSize() + getStatusOfBlockShift()) = false;
    }
    if(!*reinterpret_cast<bool *>(reinterpret_cast<byte *>(at) + sizeOfAt + getStatusOfBlockShift()) && (reinterpret_cast<byte *>(at) + sizeOfAt) != (reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift()))) {
        //За новым стоит совбодный
        //Взяли размер следующего блока
        auto sizeOfNextBlock = *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + sizeOfAt + getSizeOfBlockShift());
        //К нашему размеру добавили размер следующего
        sizeOfAt = *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + getSizeOfBlockShift()) += sizeOfNextBlock;
        //Кладём новый размер в правую мету
        *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(at) + sizeOfAt - getLocalMetaSize() + getSizeOfBlockShift()) = sizeOfAt;
    }
    //Тут else не нужен тк в предыдущем наш блок пометился свободным
    //throw not_implemented("void allocator_boundary_tags::deallocate(void *)", "your code should be here...");
}

inline void allocator_boundary_tags::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    if(_trusted_memory == nullptr) return;
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<byte *>(_trusted_memory) + getFitModeShift()) = mode;
    //throw not_implemented("inline void allocator_boundary_tags::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_boundary_tags::get_allocator() const
{
    if(_trusted_memory == nullptr) return nullptr;
    return *reinterpret_cast<allocator **>(reinterpret_cast<byte *>(_trusted_memory) + getAllocatorShift());
    //throw not_implemented("inline allocator *allocator_boundary_tags::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept
{
    std::vector<allocator_test_utils::block_info> result;
    if(_trusted_memory == nullptr) return result;
    byte *pNow = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift(), *pLast = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    while(reinterpret_cast<void *>(pNow) < reinterpret_cast<void *>(pLast)) {
        result.emplace_back(*reinterpret_cast<size_t *>(pNow + getSizeOfBlockShift()), *reinterpret_cast<bool *>(pNow + getStatusOfBlockShift()));
        pNow += *reinterpret_cast<size_t *>(pNow + getSizeOfBlockShift());
    }
    return result;
    //throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_boundary_tags::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_boundary_tags::get_logger() const
{
    if(_trusted_memory == nullptr) return nullptr;
    return *reinterpret_cast<logger **>(reinterpret_cast<byte *>(_trusted_memory) + getLoggerShift());
    //throw not_implemented("inline logger *allocator_boundary_tags::get_logger() const", "your code should be here...");
}

inline std::string allocator_boundary_tags::get_typename() const noexcept
{
    return ("allocator_boundary_tags");
    //throw not_implemented("inline std::string allocator_boundary_tags::get_typename() const noexcept", "your code should be here...");
}