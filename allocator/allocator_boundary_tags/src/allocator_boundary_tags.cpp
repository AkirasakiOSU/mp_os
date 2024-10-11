#include <not_implemented.h>

#include "../include/allocator_boundary_tags.h"

#include <mutex>

constexpr size_t allocator_boundary_tags::getGlobalMetaSize() {
    return sizeof(size_t) + sizeof(logger *) + sizeof(allocator *) + sizeof(allocator_with_fit_mode::fit_mode) + sizeof(std::mutex);
}

constexpr size_t allocator_boundary_tags::getLocalMetaSize() {
    return sizeof(bool) + sizeof(size_t);
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

constexpr size_t allocator_boundary_tags::getStatusOfBlockShift() {
    return 0;
}

constexpr size_t allocator_boundary_tags::getSizeOfBlockShift() {
    return getStatusOfBlockShift() + sizeof(bool);
}

void allocator_boundary_tags::initializationOfLocalMeta(byte *ptr, size_t sizeOfBlock, bool statusOfBlock) {
    *reinterpret_cast<bool *>(ptr + getStatusOfBlockShift()) = statusOfBlock;
    *reinterpret_cast<size_t *>(ptr + getSizeOfBlockShift()) = sizeOfBlock;
}

void allocator_boundary_tags::freeMemory() {
    if(_trusted_memory == nullptr) return;
    destruct(reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()));
    if(get_allocator() == nullptr) ::operator delete(_trusted_memory);
    else get_allocator()->deallocate(_trusted_memory);
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
    reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(other._trusted_memory) + getMutexShift()) ->lock();
    _trusted_memory = other._trusted_memory;
    other._trusted_memory = nullptr;
    reinterpret_cast<std::mutex *>(reinterpret_cast<byte *>(_trusted_memory) + getMutexShift()) ->unlock();
    //throw not_implemented("allocator_boundary_tags::allocator_boundary_tags(allocator_boundary_tags &&) noexcept", "your code should be here...");
}

allocator_boundary_tags &allocator_boundary_tags::operator=(
    allocator_boundary_tags &&other) noexcept
{
    if(this != &other) {
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
    throw not_implemented("[[nodiscard]] void *allocator_boundary_tags::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_boundary_tags::deallocate(
    void *at)
{
    throw not_implemented("void allocator_boundary_tags::deallocate(void *)", "your code should be here...");
}

inline void allocator_boundary_tags::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    if(_trusted_memory == nullptr) return;
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
    byte *pNow = reinterpret_cast<byte *>(_trusted_memory) + getFirstBlockShift();
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