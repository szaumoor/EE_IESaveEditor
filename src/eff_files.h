#ifndef EFF_FILES_H
#define EFF_FILES_H

#include "xref.h"
#include "aliases.h"

#pragma pack(push, 1)
struct EffFileV1
{
    u16 opcode;                // 0x00
    u8 target;                 // 0x02
    u8 power;                  // 0x03
    u32 parameter1;            // 0x04
    u32 parameter2;            // 0x08
    u8 timing_mode;            // 0x0C
    u8 dispel_resistance;      // 0x0D
    u32 duration;              // 0x10
    u8 probabilities[2];       // 0x12 - 0x13
    Resref keyword;           // 0x14
    u32 dice_throw_max_level;  // 0x1C
    u32 dice_sides_min_level;  // 0x20
    u32 saving_throw_type;     // 0x24
    u32 saving_throw_bonus;    // 0x28
    u32 special;               // 0x2C
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EffFileV2Header
{
    CharArray<4> signature;         // 0x00 "EFF "
    CharArray<4> version;           // 0x04 "V2.0"
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EmbeddedEffFileV2
{
    EffFileV2Header header;         // 0x00
    u32 opcode;                // 0x08
    u32 target;                // 0x0C
    u32 power;                 // 0x10
    u32 unused0;               // 0x14
    u32 unused1;               // 0x18
    u32 timing_mode;           // 0x1C
    u32 duration;              // 0x20
};
#pragma pack(pop)

#endif