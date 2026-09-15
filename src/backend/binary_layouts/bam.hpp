#ifndef EE_SAVEEDITOR_BAM_H
#define EE_SAVEEDITOR_BAM_H


#include "../utils/aliases.hpp"
#include "../utils/helper_structs.hpp"

#include <type_traits>

#pragma pack(push, 1)

struct BamV2Header
{
    CharArray<4>  signature;
    CharArray<4>  version;

    u32           frame_count;
    u32           cycle_count;
    u32           data_block_count;

    u32           frame_entries_offset;
    u32           cycle_entries_offset;
    u32           data_blocks_offset;
};

struct BamV2FrameEntry
{
    u16  width;
    u16  height;

    i16  center_x;
    i16  center_y;

    u16  data_block_start;
    u16  data_block_count;
};

struct BamV2CycleEntry
{
    u16  frame_count;
    u16  frame_start;
};

struct BamV2DataBlock
{
    u32  pvrz_page;

    u32  src_x;
    u32  src_y;
    u32  width;
    u32  height;

    u32  dst_x;
    u32  dst_y;
};

#pragma pack(pop)


#pragma region Asserts

static_assert( std::is_trivially_copyable_v<BamV2CycleEntry> );
static_assert( std::is_standard_layout_v<BamV2CycleEntry> );
static_assert(sizeof(BamV2CycleEntry) == 0x04);

static_assert( std::is_trivially_copyable_v<BamV2DataBlock> );
static_assert( std::is_standard_layout_v<BamV2DataBlock> );
static_assert(sizeof(BamV2DataBlock)  == 0x1C);

static_assert( std::is_trivially_copyable_v<BamV2FrameEntry> );
static_assert( std::is_standard_layout_v<BamV2FrameEntry> );
static_assert(sizeof(BamV2FrameEntry) == 0x0C);

static_assert( std::is_trivially_copyable_v<BamV2Header> );
static_assert( std::is_standard_layout_v<BamV2Header> );
static_assert(sizeof(BamV2Header)     == 0x20);

#pragma endregion

#endif //EE_SAVEEDITOR_BAM_H
