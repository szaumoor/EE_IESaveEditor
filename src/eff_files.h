#ifndef EFF_FILES_H
#define EFF_FILES_H

#include "aliases.h"
#include "helper_structs.h"

#pragma pack(push, 1)
struct EmbeddedEffFileV1
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
    Resref keyword;            // 0x14
    u32 dice_throw_max_level;  // 0x1C
    u32 dice_sides_min_level;  // 0x20
    u32 saving_throw_type;     // 0x24
    u32 saving_throw_bonus;    // 0x28
    u32 special;               // 0x2C
};

struct EmbeddedEffFileV2
{
    CharArray<4> signature;      // 0x00
    CharArray<4> version;        // 0x04
    u32 opcode;                  // 0x08
    u32 target;                  // 0x0C
    u32 power;                   // 0x10
    u32 parameter1;              // 0x14
    u32 parameter2;              // 0x18
    u32 timing_mode;             // 0x1C
    u32 duration;                // 0x20
    u16 probabilities[2];        // 0x24 - 0x26
    Resref resource1;            // 0x28
    u32 dice_thrown;             // 0x30
    u32 dice_sides;              // 0x34
    u32 saving_throw_type;       // 0x38
    u32 saving_throw_bonus;      // 0x3C
    u32 special;                 // 0x40
    u32 primary_type_school;     // 0x44
    u32 used_internally;         // 0x48
    u32 minimum_level;           // 0x4C
    u32 maximum_level;           // 0x50
    u32 dispel_resistance;       // 0x54
    u32 parameter3;              // 0x58
    u32 parameter4;              // 0x5C
    u32 parameter5;              // 0x60
    u32 time_applied_ticks;      // 0x64
    Resref resource2;            // 0x68
    Resref resource3;            // 0x70
    u32 caster_location_x;       // 0x78
    u32 caster_location_y;       // 0x7C
    u32 target_location_x;       // 0x80
    u32 target_location_y;       // 0x84
    u32 resource_type;           // 0x88
    Resref parent_resource;      // 0x8C
    u32 resource_flags;          // 0x94
    u32 impact_projectile;       // 0x98
    u32 source_item_slot;        // 0x9C
    CharArray<32> variable_name; // 0xA0
    u32 caster_level;            // 0xC0
    u32 internal_flags;          // 0xC4
    u32 secondary_type;          // 0xC8
    u8 unknown[60];              // 0xCC
};

#pragma pack(pop)

#endif
