#include <not_implemented.h>

#include "../include/allocator_buddies_system.h"
#include <cmath>
#include <mutex>

constexpr size_t allocator_buddies_system::getGlobalMetaSize() {
    return sizeof(size_t) + sizeof(allocator *) + sizeof(logger *) + sizeof(void *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(std::mutex);
}

constexpr size_t allocator_buddies_system::getFreeBlockMetaSize() {
    return 2 * sizeof(void *) + sizeof(byte);
}

constexpr size_t allocator_buddies_system::getOcupiedBlockMetaSize() {
    return sizeof(byte) + sizeof(void *);
}

constexpr size_t allocator_buddies_system::getSizeOfTrustedMemoryShift() {
    return 0;
}

constexpr size_t allocator_buddies_system::getAllocatorShift() {
    return sizeof(size_t);
}

constexpr size_t allocator_buddies_system::getLoggerShift() {
    return getAllocatorShift() + sizeof(allocator *);
}

constexpr size_t allocator_buddies_system::getFirstFreeBlockShift() {
    return getLoggerShift() + sizeof(logger *);
}

constexpr size_t allocator_buddies_system::getFitModeShift() {
    return getFirstFreeBlockShift() + sizeof(void *);
}

constexpr size_t allocator_buddies_system::getMutexShift() {
    return getFitModeShift() + sizeof(allocator_with_fit_mode::fit_mode);
}

constexpr size_t allocator_buddies_system::getPPrevShift() {
    return 0;
}

constexpr size_t allocator_buddies_system::getPNextShift() {
    return sizeof(void *);
}

constexpr size_t allocator_buddies_system::getSizeOfFreeBlockShift() {
    return getPNextShift() + sizeof(void *);
}

constexpr size_t allocator_buddies_system::getTMPointerShift() {
    return 0;
}

constexpr size_t allocator_buddies_system::getSizeOfOcupiedBlockShift() {
    return sizeof(void *);
}

void allocator_buddies_system::freeMemory() {
    if(_trusted_memory == nullptr) return;
    destruct(reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    deallocate_with_guard(_trusted_memory);
    _trusted_memory = nullptr;
}

void *allocator_buddies_system::allocateFirstFit(byte sizeOfNewBlock) {
    void *curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift());
    while(curBlock != nullptr) {
        byte sizeOfCurBlock = *(reinterpret_cast<byte *>(curBlock) + getSizeOfFreeBlockShift());
        if(sizeOfCurBlock == sizeOfNewBlock) return allocateBlock(curBlock);
        if(sizeOfCurBlock > sizeOfNewBlock) return divideBlock(curBlock, sizeOfNewBlock);
        curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(curBlock) + getPNextShift());
    }
    throw std::bad_alloc();
}

void *allocator_buddies_system::allocateBestFit(byte sizeOfNewBlock) {
    void *bestBlock = nullptr,
    *curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift());
    byte sizeOfBestBlock = 0;
    while(curBlock != nullptr) {
        byte sizeOfCurBlock = *(reinterpret_cast<byte *>(curBlock) + getSizeOfFreeBlockShift());
        if(sizeOfCurBlock >= sizeOfNewBlock) {
            if(sizeOfCurBlock == sizeOfNewBlock) return allocateBlock(curBlock);
            if(bestBlock == nullptr || sizeOfBestBlock > sizeOfCurBlock) {
                bestBlock = curBlock;
                sizeOfBestBlock = sizeOfCurBlock;
            }
        }
        curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(curBlock) + getPNextShift());
    }
    if(bestBlock == nullptr) throw std::bad_alloc();
    return divideBlock(bestBlock, sizeOfNewBlock);
}

void *allocator_buddies_system::allocateWorstFit(byte sizeOfNewBlock) {
    void *worstBlock = nullptr,
    *curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift());
    byte sizeOfWorstBlock = 0;
    while(curBlock != nullptr) {
        byte sizeOfCurBlock = *(reinterpret_cast<byte *>(curBlock) + getSizeOfFreeBlockShift());
        if(sizeOfCurBlock >= sizeOfNewBlock) {
            if(worstBlock == nullptr || sizeOfWorstBlock < sizeOfCurBlock) {
                worstBlock = curBlock;
                sizeOfWorstBlock = sizeOfCurBlock;
            }
        }
        curBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(curBlock) + getPNextShift());
    }
    if(worstBlock == nullptr) throw std::bad_alloc();
    if(sizeOfWorstBlock == sizeOfNewBlock) return allocateBlock(curBlock);
    return divideBlock(worstBlock, sizeOfNewBlock);
}

void *allocator_buddies_system::allocateBlock(void *block) {
    void *previous_block = *reinterpret_cast<void **>(reinterpret_cast<byte *>(block) + getPPrevShift()),
    *nextBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(block) + getPNextShift());
    byte sizeOfBlock = *(reinterpret_cast<byte *>(block) + getSizeOfFreeBlockShift());
    if(previous_block != nullptr)
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(previous_block) + getPNextShift()) = nextBlock;
    else
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift()) = nextBlock;
    if(nextBlock != nullptr)
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(nextBlock) + getPPrevShift()) = previous_block;
    *reinterpret_cast<void **>(reinterpret_cast<byte *>(block) + getTMPointerShift()) = _trusted_memory;
    *(reinterpret_cast<byte *>(block) + getSizeOfOcupiedBlockShift()) = sizeOfBlock;
    return reinterpret_cast<byte *>(block) + getOcupiedBlockMetaSize();
}

void *allocator_buddies_system::divideBlock(void *block, byte requestedSize) {
    byte sizeOfBlock = *(reinterpret_cast<byte *>(block) + getSizeOfFreeBlockShift());
    while(sizeOfBlock > requestedSize) {
        void *nextBlock = *reinterpret_cast<void **>(reinterpret_cast<byte *>(block) + getPNextShift());
        --sizeOfBlock;
        //заполним мету двойника
        void *buddy = reinterpret_cast<byte *>(block) + (1 << sizeOfBlock);
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(buddy) + getPPrevShift()) = block;
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(buddy) + getPNextShift()) = nextBlock;
        if(nextBlock != nullptr) *reinterpret_cast<void **>(reinterpret_cast<byte *>(nextBlock) + getPPrevShift()) = buddy;
        *(reinterpret_cast<byte *>(buddy) + getSizeOfFreeBlockShift()) = sizeOfBlock;
        //Заполним нашу мету
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(block) + getPNextShift()) = buddy;
        *(reinterpret_cast<byte *>(block) + getSizeOfFreeBlockShift()) = sizeOfBlock;
    }
    return allocateBlock(block);
}

void allocator_buddies_system::uniteBlock(void *at) {
    if(at == nullptr) throw;
    void *pPrev = *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPPrevShift()),
         *pNext = *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPNextShift());
    if(pPrev == nullptr && pNext == nullptr) return;
    byte sizeOfAt = *(reinterpret_cast<byte *>(at) + getSizeOfFreeBlockShift());
    size_t relativePtrOfAt = getRelativePTR(at),
    relativePtrOfBuddy = relativePtrOfAt ^ (1 << sizeOfAt);
    void *buddy = reinterpret_cast<byte *>(_trusted_memory) + getGlobalMetaSize() + relativePtrOfBuddy;
    bool buddyIsOcupied = *reinterpret_cast<void **>(reinterpret_cast<byte *>(buddy) + getTMPointerShift()) == _trusted_memory;
    if(buddyIsOcupied) return;
    byte sizeOfBuddy = *(reinterpret_cast<byte *>(buddy) + getSizeOfFreeBlockShift());
    if(sizeOfAt != sizeOfBuddy) return;
    if(at < buddy) {
        std::swap(at, buddy);
    }
    ++*(reinterpret_cast<byte *>(buddy) + getSizeOfFreeBlockShift());
    pNext = *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPNextShift());
    *reinterpret_cast<void **>(reinterpret_cast<byte *>(buddy) + getPNextShift()) = pNext;
    if(pNext != nullptr)
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(pNext) + getPPrevShift()) = buddy;
    uniteBlock(buddy);
}

size_t allocator_buddies_system::getRelativePTR(void *at) {
    byte *pFirst = reinterpret_cast<byte *>(_trusted_memory) + getGlobalMetaSize();
    return reinterpret_cast<byte *>(at) - pFirst;
}

byte allocator_buddies_system::getMinimalShiftOfBlockSize(size_t const &sizeOfBlock) {
    //for(shift = 0; sizeOfBlock < (1 << shift); ++shift){}
    byte minimalShift = static_cast<byte>(std::log2(getFreeBlockMetaSize()));
    if(sizeOfBlock <= getFreeBlockMetaSize()) return minimalShift + 1;
    byte shift = 0;
    while(sizeOfBlock > (1 << shift++)){}
    return shift - 1;
}

allocator_buddies_system::~allocator_buddies_system()
{
    freeMemory();
    //throw not_implemented("allocator_buddies_system::~allocator_buddies_system()", "your code should be here...");
}

allocator_buddies_system::allocator_buddies_system(
    allocator_buddies_system &&other) noexcept :
    _trusted_memory(nullptr)
{
    if(other._trusted_memory == nullptr) return;
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(other._trusted_memory)));
    _trusted_memory = other._trusted_memory;
    other._trusted_memory = nullptr;
    //throw not_implemented("allocator_buddies_system::allocator_buddies_system(allocator_buddies_system &&) noexcept", "your code should be here...");
}

allocator_buddies_system &allocator_buddies_system::operator=(
    allocator_buddies_system &&other) noexcept
{
    if(this != &other) {
        std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(other._trusted_memory)));
        freeMemory();
        _trusted_memory = other._trusted_memory;
        other._trusted_memory = nullptr;
    }
    return *this;
    //throw not_implemented("allocator_buddies_system &allocator_buddies_system::operator=(allocator_buddies_system &&) noexcept", "your code should be here...");
}

allocator_buddies_system::allocator_buddies_system(
    size_t space_size,
    allocator *parent_allocator,
    logger *logger,
    allocator_with_fit_mode::fit_mode allocate_fit_mode) :
    _trusted_memory(nullptr)
{
    size_t sizeOfTrustedMemory = getGlobalMetaSize() + (1 << space_size);
    if(1 << space_size < getFreeBlockMetaSize()) throw std::logic_error("Space size is small");
    try {
        _trusted_memory = (parent_allocator == nullptr ?
        ::operator new(sizeOfTrustedMemory) :
        parent_allocator->allocate(1, sizeOfTrustedMemory));
    }
    catch(std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }

    byte *tm = reinterpret_cast<byte *>(_trusted_memory), *firstBlock = tm + getGlobalMetaSize();
    *reinterpret_cast<size_t *>(tm + getSizeOfTrustedMemoryShift()) = sizeOfTrustedMemory;
    *reinterpret_cast<allocator **>(tm + getAllocatorShift()) = parent_allocator;
    *reinterpret_cast<class logger **>(tm + getLoggerShift()) = logger;
    *reinterpret_cast<void **>(tm + getFirstFreeBlockShift()) = reinterpret_cast<void *>(firstBlock);
    *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(tm + getFitModeShift()) = allocate_fit_mode;
    construct(reinterpret_cast<std::mutex *>(tm + getMutexShift()));

    *reinterpret_cast<void **>(firstBlock + getPPrevShift()) = nullptr;
    *reinterpret_cast<void **>(firstBlock + getPNextShift()) = nullptr;
    *(firstBlock + getSizeOfFreeBlockShift()) = static_cast<byte>(space_size);
    //throw not_implemented("allocator_buddies_system::allocator_buddies_system(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_buddies_system::allocate(
    size_t value_size,
    size_t values_count)
{
    if(_trusted_memory == nullptr) throw std::bad_alloc();
    if(*reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift()) == nullptr) throw std::bad_alloc();
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    auto fit = *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<byte *>(_trusted_memory) + getFitModeShift());
    byte sizeOfNewBlockShift = getMinimalShiftOfBlockSize(getOcupiedBlockMetaSize() + (value_size * values_count));
    switch (fit) {
        case allocator_with_fit_mode::fit_mode::first_fit:
            return allocateFirstFit(sizeOfNewBlockShift);
            break;
        case allocator_with_fit_mode::fit_mode::the_best_fit:
            return allocateBestFit(sizeOfNewBlockShift);
            break;
        case allocator_with_fit_mode::fit_mode::the_worst_fit:
            return allocateWorstFit(sizeOfNewBlockShift);
            break;
        default:
            throw std::runtime_error("Unknown fitMode");
    }
    //throw not_implemented("[[nodiscard]] void *allocator_buddies_system::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_buddies_system::deallocate(
    void *at)
{
    if(at == nullptr) return;
    if(_trusted_memory == nullptr) throw std::logic_error("Allocator is empty");
    at = reinterpret_cast<byte *>(at) - getOcupiedBlockMetaSize();
    void *pFirst = reinterpret_cast<byte *>(_trusted_memory) + getGlobalMetaSize(),
        *pLast = reinterpret_cast<byte *>(_trusted_memory) + *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    if(at < pFirst || at > pLast) throw std::logic_error("Ptr is non consists to that allocator");
    if(*reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getTMPointerShift()) != _trusted_memory) throw std::logic_error("Ptr not belong to that allocator");
    void *pRight = *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift());
    byte sizeOfBlock = *(reinterpret_cast<byte *>(at) + getSizeOfOcupiedBlockShift());
    if(pRight == nullptr) {
        //У нас нет ни одного блока :(
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift()) = at;
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPPrevShift()) = nullptr;
        *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPNextShift()) = nullptr;
        *(reinterpret_cast<byte *>(at) + getSizeOfFreeBlockShift()) = sizeOfBlock;
        return;
    }
    while(true) {
        if(at < pRight) {
            //Нашли перед каким блоком стоит наш at
            void *pLeft = *reinterpret_cast<void **>(reinterpret_cast<byte *>(pRight) + getPPrevShift());
            *reinterpret_cast<void **>(reinterpret_cast<byte *>(pRight) + getPPrevShift()) = at;
            *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPNextShift()) = pRight;
            *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPPrevShift()) = pLeft;
            if(pLeft == nullptr)
                *reinterpret_cast<void **>(reinterpret_cast<byte *>(_trusted_memory) + getFirstFreeBlockShift()) = at;
            else
                *reinterpret_cast<void **>(reinterpret_cast<byte *>(pLeft) + getPNextShift()) = at;
            *(reinterpret_cast<byte *>(at) + getSizeOfFreeBlockShift()) = sizeOfBlock;
            uniteBlock(at);
            return;
        }
        if(*reinterpret_cast<void **>(reinterpret_cast<byte *>(pRight) + getPNextShift()) == nullptr) break;
        pRight = *reinterpret_cast<void **>(reinterpret_cast<byte *>(pRight) + getPNextShift());
    }
    //Если наш блок будет последним
    *reinterpret_cast<void **>(reinterpret_cast<byte *>(pRight) + getPNextShift()) = at;
    *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPPrevShift()) = pRight;
    *reinterpret_cast<void **>(reinterpret_cast<byte *>(at) + getPNextShift()) = nullptr;
    *(reinterpret_cast<byte *>(at) + getSizeOfFreeBlockShift()) = sizeOfBlock;
    uniteBlock(at);
    //throw not_implemented("void allocator_buddies_system::deallocate(void *)", "your code should be here...");
}

inline void allocator_buddies_system::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    if(_trusted_memory == nullptr) return;
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory)));
    *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<byte *>(_trusted_memory) + getFitModeShift()) = mode;
    //throw not_implemented("inline void allocator_buddies_system::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_buddies_system::get_allocator() const
{
    if(_trusted_memory == nullptr) return nullptr;
    return *reinterpret_cast<allocator **>(reinterpret_cast<byte *>(_trusted_memory) + getAllocatorShift());
    //throw not_implemented("inline allocator *allocator_buddies_system::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info() const noexcept
{
    std::vector<allocator_test_utils::block_info> result;
    if(_trusted_memory == nullptr) return result;
    auto sizeOfTrustedMemory =  *reinterpret_cast<size_t *>(reinterpret_cast<byte *>(_trusted_memory) + getSizeOfTrustedMemoryShift());
    byte *pNow = reinterpret_cast<byte *>(_trusted_memory) +getGlobalMetaSize(),
    *pLast = reinterpret_cast<byte *>(_trusted_memory) + sizeOfTrustedMemory;
    while(pNow < pLast) {
        bool isOcupated = (*reinterpret_cast<void **>(pNow) == _trusted_memory);
        byte shift = *(pNow + (isOcupated ? getSizeOfOcupiedBlockShift() : getSizeOfFreeBlockShift()));
        size_t sizeOfBlock = 1 << shift;
        result.emplace_back(sizeOfBlock, isOcupated);
        pNow = reinterpret_cast<byte *>(pNow) + sizeOfBlock;
    }
    return result;
    //throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_buddies_system::get_logger() const
{
    if(_trusted_memory == nullptr) return nullptr;
    return *reinterpret_cast<logger **>(reinterpret_cast<byte *>(_trusted_memory) + getLoggerShift());
    //throw not_implemented("inline logger *allocator_buddies_system::get_logger() const", "your code should be here...");
}

inline std::string allocator_buddies_system::get_typename() const noexcept
{
    return ("allocator_buddies_system");
    //throw not_implemented("inline std::string allocator_buddies_system::get_typename() const noexcept", "your code should be here...");
}