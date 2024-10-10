#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_SORTED_LIST_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_SORTED_LIST_H

#include <allocator_guardant.h>
#include <allocator_test_utils.h>
#include <allocator_with_fit_mode.h>
#include <logger_guardant.h>
#include <mutex>
#include <typename_holder.h>



class allocator_sorted_list final:
    private allocator_guardant,
    public allocator_test_utils,
    public allocator_with_fit_mode,
    private logger_guardant,
    private typename_holder
{

    static constexpr size_t getGlobalMetaSize();
    static constexpr size_t getLocalMetaSize();
    static constexpr size_t getTrustedMemorySizeShift();
    static constexpr size_t getAllocatorShift();
    static constexpr size_t getLoggerShift();
    static constexpr size_t getMutexShift();
    static constexpr size_t getFirstFreeMemoryShift();
    static constexpr size_t getFitModeShift();
    static constexpr size_t getFirstByteOfTrustedMemory();

    static constexpr size_t getSizeOfBlockShift();
    static constexpr size_t getFirstByteOfBlock();

    size_t getFreeMemorySize() const;
    void logBlockСondition(void *) const;
    void logTrustedMemoryCondition() const;

private:
    void *_trusted_memory;

    void freeMemory();

    void *allocateFullBlock(void *, void *);
    void *allocateBlock(void *, void *, size_t);

    void *allocateFirstFit(size_t);
    void *allocateBestFit(size_t);
    void *allocateWorstFit(size_t);

public:
    
    ~allocator_sorted_list() override;
    
    allocator_sorted_list(
        allocator_sorted_list const &other) = delete;
    
    allocator_sorted_list &operator=(
        allocator_sorted_list const &other) = delete;
    
    allocator_sorted_list(
        allocator_sorted_list &&other) noexcept;
    
    allocator_sorted_list &operator=(
        allocator_sorted_list &&other) noexcept;

public:
    
    explicit allocator_sorted_list(
        size_t space_size,
        allocator *parent_allocator = nullptr,
        logger *logger = nullptr,
        allocator_with_fit_mode::fit_mode allocate_fit_mode = allocator_with_fit_mode::fit_mode::first_fit);

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

public:
    
    inline void set_fit_mode(
        allocator_with_fit_mode::fit_mode mode) override;

private:
    
    inline allocator *get_allocator() const override;

public:
    
    std::vector<allocator_test_utils::block_info> get_blocks_info() const noexcept override;

private:
    
    inline logger *get_logger() const override;

private:
    
    inline std::string get_typename() const noexcept override;
    
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_SORTED_LIST_H