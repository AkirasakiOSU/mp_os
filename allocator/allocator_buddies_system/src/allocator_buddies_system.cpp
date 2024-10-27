#include <not_implemented.h>

#include "../include/allocator_buddies_system.h"

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
    return getPPrevShift() + sizeof(void *);
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
    if(space_size > UCHAR_MAX) throw std::runtime_error("Не придумал :3");
    size_t sizeOfTrustedMemory = getGlobalMetaSize() + (1 << space_size);
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
    std::lock_guard<std::mutex> locker(*reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    auto fit = *reinterpret_cast<allocator_with_fit_mode::fit_mode *>(reinterpret_cast<byte *>(_trusted_memory) + getFitModeShift());
    auto sizeOfNewBlock = getOcupiedBlockMetaSize() + (value_size * values_count);
    switch (fit) {
        case allocator_with_fit_mode::fit_mode::first_fit:
            return allocateFirstFit(sizeOfNewBlock);
            break;
        case allocator_with_fit_mode::fit_mode::the_best_fit:
            return allocateBestFit(sizeOfNewBlock);
            break;
        case allocator_with_fit_mode::fit_mode::the_worst_fit:
            return allocateWorstFit(sizeOfNewBlock);
            break;
        default:
            throw std::runtime_error("Unknown fitMode");
    }
    //throw not_implemented("[[nodiscard]] void *allocator_buddies_system::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_buddies_system::deallocate(
    void *at)
{
    throw not_implemented("void allocator_buddies_system::deallocate(void *)", "your code should be here...");
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