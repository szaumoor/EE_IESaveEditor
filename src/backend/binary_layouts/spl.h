#ifndef EE_SAVEEDITOR_SPL_H
#define EE_SAVEEDITOR_SPL_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#pragma pack(push, 1)

struct SplHeader
{
    CharArray<4>  signature;              // 0x0000  "SPL "
    CharArray<4>  version;                // 0x0004  "V1  "

    u32           name_unidentified;       // 0x0008  strref
    u32           name_identified;         // 0x000C  strref (usually -1, unused)

    CharArray<8>  completion_sound;        // 0x0010  resref
    u32           flags;                   // 0x0018

    u16           spell_type;              // 0x001C  enum
    u32           exclusion_flags;         // 0x001E

    u16           casting_graphics;        // 0x0022

    u8            min_level;               // 0x0024  unused
    u8            primary_type;            // 0x0025  school
    u8            min_strength;            // 0x0026  unused
    u8            secondary_type;          // 0x0027  sectype

    u8            min_strength_bonus;      // 0x0028  unused
    u8            usability_1;             // 0x0029  unused
    u8            min_intelligence;        // 0x002A  unused
    u8            usability_2;             // 0x002B  unused
    u8            min_dexterity;           // 0x002C  unused
    u8            usability_3;             // 0x002D  unused
    u8            min_wisdom;              // 0x002E  unused
    u8            usability_4;             // 0x002F  unused

    u16           min_constitution;        // 0x0030  unused
    u16           min_charisma;            // 0x0032  unused

    u32           spell_level;             // 0x0034

    u16           stack_amount;            // 0x0038  unused
    CharArray<8>  spellbook_icon;          // 0x003A  BAM resref (last char → 'C')

    u16           lore_to_id;               // 0x0042  unused
    CharArray<8>  ground_icon;             // 0x0044  unused

    u32           weight;                  // 0x004C  unused

    u32           desc_unidentified;       // 0x0050  strref
    u32           desc_identified;         // 0x0054  strref (usually -1, unused)

    CharArray<8>  description_icon;        // 0x0058  unused
    u32           enchantment;             // 0x0060  unused

    u32           ext_header_offset;        // 0x0064
    u16           ext_header_count;         // 0x0068

    u32           feature_block_offset;    // 0x006A
    u16           casting_feature_offset;  // 0x006E
    u16           casting_feature_count;   // 0x0070
};

struct SplExtendedHeader
{
    u8   spell_form;                // 0x0000  1=Standard, 2=Projectile (SPL mostly irrelevant)
    u8   flags;                     // 0x0001  bit 2 = Friendly (PST only)

    u16  location;                  // 0x0002  ability location (0=None, 2=Spell, 4=Innate, etc.)

    CharArray<8> memorised_icon;    // 0x0004  BAM resref (last char → 'B')

    u8   target;                    // 0x000C  target type
    u8   target_count;              // 0x000D  number of targets (UI only)

    u16  range;                     // 0x000E  range

    u16  level_required;            // 0x0010  casting level required
    u16  casting_time;              // 0x0012  tenths of rounds

    u16  times_per_day;             // 0x0014
    u16  dice_sides;                // 0x0016  unused
    u16  dice_thrown;               // 0x0018  unused
    u16  enchanted;                 // 0x001A  unused
    u16  damage_type;               // 0x001C  unused

    u16  feature_block_count;       // 0x001E
    u16  feature_block_offset;      // 0x0020

    u16  charges;                   // 0x0022  unused
    u16  charge_depletion;          // 0x0024  unused

    u16  projectile;                // 0x0026  projectl.ids (BG2 off-by-one)
};

#pragma pack(pop)

static_assert(sizeof(SplExtendedHeader) == 0x28, "SplExtendedHeader size mismatch");
static_assert(sizeof(SplHeader) == 0x72, "SplHeader size mismatch");

#endif //EE_SAVEEDITOR_SPL_H