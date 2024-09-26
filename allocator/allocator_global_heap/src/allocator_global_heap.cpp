#include <not_implemented.h>

#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap(
    logger *logger) :
    _logger(logger)
{
    //throw not_implemented("allocator_global_heap::allocator_global_heap(logger *)", "your code should be here...");
}

allocator_global_heap::~allocator_global_heap()
{
    _logger = nullptr;
    //throw not_implemented("allocator_global_heap::~allocator_global_heap()", "your code should be here...");
}

allocator_global_heap::allocator_global_heap(
    allocator_global_heap &&other) noexcept
{
    _logger = other._logger;
    other._logger = nullptr;
    //throw not_implemented("allocator_global_heap::allocator_global_heap(allocator_global_heap &&) noexcept", "your code should be here...");
}

allocator_global_heap &allocator_global_heap::operator=(
    allocator_global_heap &&other) noexcept
{
    if(this != &other) {
        _logger = other._logger;
        other._logger = nullptr;
    }
    return *this;
    //throw not_implemented("allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&) noexcept", "your code should be here...");
}

[[nodiscard]] void *allocator_global_heap::allocate(
    size_t value_size,
    size_t values_count)
{
    void *allocatedMemory = nullptr;
    try {
        allocatedMemory = ::operator new(value_size * values_count);
    }
    catch (std::bad_alloc const &e) {
        return nullptr;
    }
    catch (...) {
        throw std::logic_error("Unknown Error");
    }
    return allocatedMemory;
    //throw not_implemented("[[nodiscard]] void *allocator_global_heap::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_global_heap::deallocate(
    void *at)
{
    ::operator delete(at);
    //throw not_implemented("void allocator_global_heap::deallocate(void *)", "your code should be here...");
}

inline logger *allocator_global_heap::get_logger() const
{
    return _logger;
    //throw not_implemented("inline logger *allocator_global_heap::get_logger() const", "your code should be here...");
}

inline std::string allocator_global_heap::get_typename() const noexcept
{
    throw not_implemented("inline std::string allocator_global_heap::get_typename() const noexcept", "your code should be here...");
}