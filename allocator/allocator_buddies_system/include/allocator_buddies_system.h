#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H

#include <allocator_guardant.h>
#include <allocator_test_utils.h>
#include <allocator_with_fit_mode.h>
#include <logger_guardant.h>
#include <typename_holder.h>

using byte = unsigned char;

class allocator_buddies_system final:
    private allocator_guardant,
    public allocator_test_utils,
    public allocator_with_fit_mode,
    private logger_guardant,
    private typename_holder
{

private:
    //friend int main();
    void *_trusted_memory;

    static constexpr size_t getGlobalMetaSize();
    static constexpr size_t getFreeBlockMetaSize();
    static constexpr size_t getOcupiedBlockMetaSize();

    static constexpr size_t getSizeOfTrustedMemoryShift();
    static constexpr size_t getAllocatorShift();
    static constexpr size_t getLoggerShift();
    static constexpr size_t getFirstFreeBlockShift();
    static constexpr size_t getFitModeShift();
    static constexpr size_t getMutexShift();

    static constexpr size_t getPPrevShift();
    static constexpr size_t getPNextShift();
    static constexpr size_t getSizeOfFreeBlockShift();

    static constexpr size_t getTMPointerShift();
    static constexpr size_t getSizeOfOcupiedBlockShift();

    void freeMemory();

    void *allocateFirstFit(byte);
    void *allocateBestFit(byte);
    void *allocateWorstFit(byte);

    void *allocateBlock(void *);

    void *divideBlock(void *, byte);
    void uniteBlock(void *);

    inline size_t getRelativePTR(void *);

    static byte getMinimalShiftOfBlockSize(size_t const &);
public:
    
    ~allocator_buddies_system() override;
    
    allocator_buddies_system(
        allocator_buddies_system const &other) = delete;
    
    allocator_buddies_system &operator=(
        allocator_buddies_system const &other) = delete;
    
    allocator_buddies_system(
        allocator_buddies_system &&other) noexcept;
    
    allocator_buddies_system &operator=(
        allocator_buddies_system &&other) noexcept;

public:
    
    explicit allocator_buddies_system(
        size_t space_size_power_of_two,
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

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_BUDDIES_SYSTEM_H
