#include <not_implemented.h>

#include "../include/allocator_sorted_list.h"


void allocator_sorted_list::freeMemory() {
    auto allocatorPtr = *(reinterpret_cast<allocator **>(_trusted_memory + LOGGER_SHIFT));
    if(allocatorPtr == nullptr) {
        ::operator delete(_trusted_memory + MUTEX_SHIFT);
        ::operator delete(_trusted_memory);
    } else {
        allocatorPtr->deallocate(_trusted_memory + MUTEX_SHIFT);
        allocatorPtr->deallocate(_trusted_memory);
    }
}

void *allocator_sorted_list::allocateFullBlock(void *pPrev, void *pNow) {
    if(*(reinterpret_cast<void **>(pNow)) == nullptr) {
        *(reinterpret_cast<void **>(pPrev)) = nullptr;
    }else {
        *(reinterpret_cast<void **>(pPrev)) = *(reinterpret_cast<void **>(pNow));
    }
    *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
    return pNow + LOCAL_META_SIZE;
}

void *allocator_sorted_list::allocateBlock(void *pPrev, void *pNow, size_t sizeOfNewBlock) {
    auto sizeOfBlock = *(reinterpret_cast<size_t *>(pNow + SIZE_OF_BLOCK_SHIFT));
    if(sizeOfBlock == sizeOfNewBlock) {
        return allocateFullBlock(pPrev, pNow);
    }
    if(sizeOfBlock > sizeOfNewBlock) {
        if(sizeOfBlock - sizeOfNewBlock < LOCAL_META_SIZE) {
            return allocateFullBlock(pPrev, pNow);
        }
        void *newFreeBlock = nullptr;
        *(reinterpret_cast<void **>(pPrev)) = newFreeBlock = pNow + sizeOfNewBlock;
        *(reinterpret_cast<void **>(newFreeBlock)) = *(reinterpret_cast<void **>(pNow));
        *(reinterpret_cast<size_t *>(newFreeBlock + SIZE_OF_BLOCK_SHIFT)) = sizeOfBlock - sizeOfNewBlock;
        *(reinterpret_cast<void **>(pNow)) = _trusted_memory;
        *(reinterpret_cast<size_t *>(pNow + SIZE_OF_BLOCK_SHIFT)) = sizeOfNewBlock;
        return pNow + LOCAL_META_SIZE;
    }
    throw std::bad_alloc();
}

void *allocator_sorted_list::allocateFirstFit(size_t size) {
    void *pPrev, *pNow;
    auto sizeOfNewBlock = size + LOCAL_META_SIZE;
    pNow = *(reinterpret_cast<void **>(pPrev = _trusted_memory + FIRST_FREE_MEMORY_SHIFT));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(pNow + SIZE_OF_BLOCK_SHIFT));
        if(sizeOfBlock >= sizeOfNewBlock) return allocateBlock(pPrev, pNow, sizeOfNewBlock);
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    throw std::bad_alloc();
    return nullptr;
}

void *allocator_sorted_list::allocateBestFit(size_t size) {
    std::pair<void *, void *> bestBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + LOCAL_META_SIZE;
    bestBlock.second = pNow = *(reinterpret_cast<void **>(bestBlock.first = pPrev = _trusted_memory + FIRST_FREE_MEMORY_SHIFT));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(pNow + SIZE_OF_BLOCK_SHIFT));
        if(sizeOfBlock == sizeOfNewBlock) return allocateFullBlock(pPrev, pNow);
        if(sizeOfBlock > sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(bestBlock.second + SIZE_OF_BLOCK_SHIFT)) > sizeOfBlock) {
                bestBlock.first = pPrev;
                bestBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        return allocateBlock(bestBlock.first, bestBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    throw std::bad_alloc();
    return nullptr;
}

void *allocator_sorted_list::allocateWorstFit(size_t size) {
    std::pair<void *, void *> worstBlock;
    void *pNow, *pPrev;
    auto sizeOfNewBlock = size + LOCAL_META_SIZE;
    worstBlock.second = pNow = *(reinterpret_cast<void **>(worstBlock.first = pPrev = _trusted_memory + FIRST_FREE_MEMORY_SHIFT));
    while(pNow != nullptr) {
        auto sizeOfBlock = *(reinterpret_cast<size_t *>(pNow + SIZE_OF_BLOCK_SHIFT));
        if(sizeOfBlock >= sizeOfNewBlock) {
            if(*(reinterpret_cast<size_t *>(worstBlock.second + SIZE_OF_BLOCK_SHIFT)) < sizeOfBlock) {
                worstBlock.first = pPrev;
                worstBlock.second = pNow;
            }
        }
        pPrev = pNow;
        pNow = *(reinterpret_cast<void **>(pNow));
    }
    try {
        return allocateBlock(worstBlock.first, worstBlock.second, sizeOfNewBlock);
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    throw std::bad_alloc();
    return nullptr;
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
    try {
        auto fullSsize = space_size + GLOBAL_META_SIZE;
        if(parent_allocator == nullptr) _trusted_memory = ::operator new(fullSsize);
        else _trusted_memory = parent_allocator->allocate(fullSsize, 1);
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() <<std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() <<std::endl;
        throw e;
    }
    void *firstBlock = nullptr;
    *(reinterpret_cast<size_t *>(_trusted_memory + TRUSTED_MEMORY_SIZE_SHIFT)) = space_size;
    *(reinterpret_cast<allocator **>(_trusted_memory + ALLOCATOR_SHIFT)) = parent_allocator;
    *(reinterpret_cast<logger **>(_trusted_memory + LOGGER_SHIFT)) = loger;
    *(reinterpret_cast<std::mutex **>(_trusted_memory + MUTEX_SHIFT)) = reinterpret_cast<std::mutex *>(((parent_allocator == nullptr) ? ::operator new(sizeof(std::mutex)) : (parent_allocator->allocate(sizeof(std::mutex), 1))));
    *(reinterpret_cast<void **>(_trusted_memory + FIRST_FREE_MEMORY_SHIFT)) = firstBlock = _trusted_memory + GLOBAL_META_SIZE;
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(_trusted_memory + FIT_MODE_SHIFT)) = allocate_fit_mode;


    *(reinterpret_cast<void **>(firstBlock)) = nullptr;
    *(reinterpret_cast<size_t *>(firstBlock + SIZE_OF_BLOCK_SHIFT)) = space_size + LOCAL_META_SIZE;
    //throw not_implemented("allocator_sorted_list::allocator_sorted_list(size_t, allocator *, logger *, allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_sorted_list::allocate(
    size_t value_size,
    size_t values_count)
{
    auto mutex = reinterpret_cast<std::mutex *>(_trusted_memory + MUTEX_SHIFT);
    mutex->lock();
    auto blockSize = value_size * values_count;
    try {
        switch (static_cast<int>(*(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(_trusted_memory + FIT_MODE_SHIFT)))) {
            case 0:
                return allocateFirstFit(blockSize);
                break;
            case 1:
                return allocateBestFit(blockSize);
                break;
            case 2:
                return allocateWorstFit(blockSize);
                break;
            default:
                throw std::bad_alloc();
                break;
        }
    }
    catch (std::bad_alloc const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }

    mutex->unlock();
    //throw not_implemented("[[nodiscard]] void *allocator_sorted_list::allocate(size_t, size_t)", "your code should be here...");
}

void allocator_sorted_list::deallocate(
    void *at)
{
    throw not_implemented("void allocator_sorted_list::deallocate(void *)", "your code should be here...");
}

inline void allocator_sorted_list::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    *(reinterpret_cast<allocator_with_fit_mode::fit_mode *>(_trusted_memory + FIT_MODE_SHIFT)) = mode;
    //throw not_implemented("inline void allocator_sorted_list::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

inline allocator *allocator_sorted_list::get_allocator() const
{
    return *(reinterpret_cast<allocator **>(_trusted_memory + ALLOCATOR_SHIFT));
    //throw not_implemented("inline allocator *allocator_sorted_list::get_allocator() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_sorted_list::get_blocks_info() const noexcept", "your code should be here...");
}

inline logger *allocator_sorted_list::get_logger() const
{
    return *(reinterpret_cast<logger **>(_trusted_memory + LOGGER_SHIFT));
    //throw not_implemented("inline logger *allocator_sorted_list::get_logger() const", "your code should be here...");
}

inline std::string allocator_sorted_list::get_typename() const noexcept
{
    return "allocator_sorted_list";
    //throw not_implemented("inline std::string allocator_sorted_list::get_typename() const noexcept", "your code should be here...");
}