#ifndef EE_SAVEEDITOR_BAM_H
#define EE_SAVEEDITOR_BAM_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#pragma pack(push, 1)

struct BamV2Header
{
    CharArray<4>  signature;              // 0x0000  "BAM "
    CharArray<4>  version;                // 0x0004  "V2  "

    u32           frame_count;             // 0x0008  number of frame entries
    u32           cycle_count;             // 0x000C  number of cycle entries
    u32           data_block_count;        // 0x0010  number of data blocks

    u32           frame_entries_offset;    // 0x0014  from file start
    u32           cycle_entries_offset;    // 0x0018  from file start
    u32           data_blocks_offset;      // 0x001C  from file start
};

struct BamV2FrameEntry
{
    u16  width;                            // 0x0000
    u16  height;                           // 0x0002

    i16  center_x;                         // 0x0004
    i16  center_y;                         // 0x0006

    u16  data_block_start;                // 0x0008  start index
    u16  data_block_count;                // 0x000A  count
};

struct BamV2CycleEntry
{
    u16  frame_count;                     // 0x0000  frames in this cycle
    u16  frame_start;                     // 0x0002  start index into frame table
};

struct BamV2DataBlock
{
    u32  pvrz_page;                       // 0x0000  MOSxxxx.PVRZ (xxxx = page)

    u32  src_x;                           // 0x0004
    u32  src_y;                           // 0x0008
    u32  width;                           // 0x000C
    u32  height;                          // 0x0010

    u32  dst_x;                           // 0x0014
    u32  dst_y;                           // 0x0018
};

#pragma pack(pop)


static_assert(sizeof(BamV2CycleEntry) == 0x04);
static_assert(sizeof(BamV2DataBlock) == 0x1C);
static_assert(sizeof(BamV2FrameEntry) == 0x0C);
static_assert(sizeof(BamV2Header) == 0x20);

#endif //EE_SAVEEDITOR_BAM_H
