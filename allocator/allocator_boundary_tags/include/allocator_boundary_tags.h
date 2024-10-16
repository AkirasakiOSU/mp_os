#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H

#include <allocator_guardant.h>
#include <allocator_test_utils.h>
#include <allocator_with_fit_mode.h>
#include <logger_guardant.h>
#include <typename_holder.h>
using byte = unsigned char;
class allocator_boundary_tags final:
    private allocator_guardant,
    public allocator_test_utils,
    public allocator_with_fit_mode,
    private logger_guardant,
    private typename_holder
{

    static constexpr size_t getGlobalMetaSize();
    static constexpr size_t getLocalMetaSize();

    static constexpr size_t getSizeOfTrustedMemoryShift();
    static constexpr size_t getLoggerShift();
    static constexpr size_t getAllocatorShift();
    static constexpr size_t getFitModeShift();
    static constexpr size_t getMutexShift();
    static constexpr size_t getFirstBlockShift();

    static constexpr size_t getStatusOfBlockShift();
    static constexpr size_t getSizeOfBlockShift();
    static constexpr size_t getTrustedMemoryPtrShift();

    void initializationOfLocalMeta(byte *, size_t, bool);

    void freeMemory();

    void *allocateFirstFit(size_t);
    void *allocateBestFit(size_t);
    void *allocateWorstFit(size_t);

    void *allocateBlock(void *, size_t);
    void *allocateFullBlock(void *);

    byte *findFirstFreeBlock(size_t) const;
private:
    
    void *_trusted_memory;

public:
    
    ~allocator_boundary_tags() override;
    
    allocator_boundary_tags(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags const &other) = delete;
    
    allocator_boundary_tags(
        allocator_boundary_tags &&other) noexcept;
    
    allocator_boundary_tags &operator=(
        allocator_boundary_tags &&other) noexcept;

public:
    
    explicit allocator_boundary_tags(
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

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BOUNDARY_TAGS_H