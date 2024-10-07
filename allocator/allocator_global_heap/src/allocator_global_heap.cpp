#include <not_implemented.h>

#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap(
    logger *logger) :
    _logger(logger)
{
    log_with_guard(std::string("allocator_global_heap()"), logger::severity::debug);
    log_with_guard(std::string("~allocator_global_heap()"), logger::severity::debug);
    //throw not_implemented("allocator_global_heap::allocator_global_heap(logger *)", "your code should be here...");
}

allocator_global_heap::~allocator_global_heap()
{
    log_with_guard(std::string("~allocator_global_heap()"), logger::severity::debug);
    _logger = nullptr;
    log_with_guard(std::string("~~allocator_global_heap()"), logger::severity::debug);
    //throw not_implemented("allocator_global_heap::~allocator_global_heap()", "your code should be here...");
}

allocator_global_heap::allocator_global_heap(
    allocator_global_heap &&other) noexcept
{
    log_with_guard(std::string("allocator_global_heap(&&);"), logger::severity::debug);
    _logger = other._logger;
    other._logger = nullptr;
    log_with_guard(std::string("~allocator_global_heap(&&)"), logger::severity::debug);
    //throw not_implemented("allocator_global_heap::allocator_global_heap(allocator_global_heap &&) noexcept", "your code should be here...");
}

allocator_global_heap &allocator_global_heap::operator=(
    allocator_global_heap &&other) noexcept
{
    log_with_guard(std::string("operator =(&&)"), logger::severity::debug);
    if(this != &other) {
        _logger = other._logger;
        other._logger = nullptr;
    }
    log_with_guard(std::string("~operator =(&&)"), logger::severity::debug);
    return *this;
    //throw not_implemented("allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&) noexcept", "your code should be here...");
}

[[nodiscard]] void *allocator_global_heap::allocate(
    size_t value_size,
    size_t values_count)
{
    log_with_guard(std::string("Allocate(") + std::to_string(value_size) + std::string(", ") + std::to_string(value_size) + std::string(");"), logger::severity::debug);
    void *allocatedMemory = nullptr;
    try {
        allocatedMemory = ::operator new(value_size * values_count);
    }
    catch (std::bad_alloc const &e) {
        log_with_guard(e.what(), logger::severity::error);
        throw e;
    }
    log_with_guard(std::string("~Allocate(") + std::to_string(value_size) + std::string(", ") + std::to_string(value_size) + std::string(");"), logger::severity::debug);
    return allocatedMemory;
    //throw not_implemented("[[nodiscard]] void *allocator_global_heap::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_global_heap::deallocate(
    void *at)
{
    log_with_guard(std::string("deallocate();"), logger::severity::debug);
    ::operator delete(at);
    log_with_guard(std::string("~deallocate();"), logger::severity::debug);
    //throw not_implemented("void allocator_global_heap::deallocate(void *)", "your code should be here...");
}

inline logger *allocator_global_heap::get_logger() const
{
    return _logger;
    //throw not_implemented("inline logger *allocator_global_heap::get_logger() const", "your code should be here...");
}

inline std::string allocator_global_heap::get_typename() const noexcept
{
    return "allocator_global_heap";
    //throw not_implemented("inline std::string allocator_global_heap::get_typename() const noexcept", "your code should be here...");
}