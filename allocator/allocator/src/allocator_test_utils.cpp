#include "../include/allocator_test_utils.h"

allocator_test_utils::block_info::block_info(size_t size, bool ocup) :
block_size(size),
is_block_occupied(ocup)
{}

bool allocator_test_utils::block_info::operator==(
    allocator_test_utils::block_info const &other) const noexcept
{
    return block_size == other.block_size
           && is_block_occupied == other.is_block_occupied;
}

bool allocator_test_utils::block_info::operator!=(
    allocator_test_utils::block_info const &other) const noexcept
{
    return !(*this == other);
}