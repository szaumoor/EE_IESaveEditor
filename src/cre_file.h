#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "xref.h"
#include <cstdint>

namespace
{
    #pragma pack(push, 1)
    struct CreHeader
    {
        CharArray<4> signature;                 // 0x0 "CRE "
        CharArray<4> version;                   // 0x4 "V1.0"
        Strref long_name;                       // 0x8
        Strref short_name;                      // 0xC
        uint32_t cre_flags;                     // 0x10
        uint32_t xp_gained_kills;               // 0x14
        uint32_t xp_creature;                   // 0x18
        uint32_t gold;                          // 0x1C
        uint32_t permanent_status_flags;        // 0x20
        uint16_t current_hit_points;            // 0x24
        uint16_t max_hit_points;                // 0x26
        uint32_t animation_id;                  // 0x28
        uint8_t metal_colour_index;             // 0x2C
        uint8_t minor_colour_index;             // 0x2D
        uint8_t major_colour_index;             // 0x2E
        uint8_t skin_colour_index;              // 0x2F
        uint8_t leather_colour_index;           // 0x30
        uint8_t armor_colour_index;             // 0x31
        uint8_t hair_colour_index;              // 0x32
        uint8_t eff_structure_version;          // 0x33
        Resref small_portrait;                  // 0x34
        Resref large_portrait;                  // 0x3C
        int8_t reputation;                      // 0x44 Minimum value: 0
        uint8_t hide_in_shadows;                // 0x45
        int16_t ac_natural;                     // 0x46
        int16_t ac_effective;                   // 0x48
        int16_t ac_crushing;                    // 0x4A
        int16_t ac_missile;                     // 0x4C
        int16_t ac_piercing;                    // 0x4E
        int16_t ac_slashing;                    // 0x50
        uint8_t thac0;                          // 0x52
        uint8_t apr;                            // 0x53
        uint8_t saving_throw_vs_death;          // 0x54
        uint8_t saving_throw_vs_wands;          // 0x55
        uint8_t saving_throw_vs_poly;           // 0x56
        uint8_t saving_throw_vs_breath;         // 0x57
        uint8_t saving_throw_vs_spell;          // 0x58
        uint8_t resist_fire;                    // 0x59
        uint8_t resist_cold;                    // 0x5A
        uint8_t resist_electricity;             // 0x5B
        uint8_t resist_acid;                    // 0x5C
        uint8_t resist_magic;                   // 0x5D
        uint8_t resist_magic_fire;              // 0x5E
        uint8_t resist_magic_cold;              // 0x5F
        uint8_t resist_slashing;                // 0x60
        uint8_t resist_crushing;                // 0x61
        uint8_t resist_piercing;                // 0x62
        uint8_t resist_missile;                 // 0x63
        uint8_t detect_illusion;                // 0x64
        uint8_t set_traps;                      // 0x65
        uint8_t lore;                           // 0x66
        uint8_t open_locks;                     // 0x67
        uint8_t move_silently;                  // 0x68
        uint8_t find_traps;                     // 0x69
        uint8_t pick_pockets;                   // 0x6A
        uint8_t fatigue;                        // 0x6B
        uint8_t intoxication;                   // 0x6C
        uint8_t luck;                           // 0x6D
        uint8_t large_sword_proficiency;        // 0x6E
        uint8_t small_sword_proficiency;        // 0x6F
        uint8_t bow_proficiency;                // 0x70
        uint8_t spear_proficiency;              // 0x71
        uint8_t blunt_proficiency;              // 0x72
        uint8_t spiked_proficiency;             // 0x73
        uint8_t axe_proficiency;                // 0x74
        uint8_t missile_proficiency;            // 0x75
        uint8_t unused_proficiencies1[5];       // 0x76 - 0x7A
        uint8_t unused_proficiencies2[7];       // 0x7B - 0x81
        uint8_t turn_undead_level;              // 0x82
        uint8_t tracking_level;                 // 0x83
        CharArray<32> tracking_target;          // 0x84
        Strref soundset_strrefs[100];          // 0xA4 - 0x230
        uint8_t class_levels[3];                // 0x234 - 0x236
        uint8_t sex;                            // 0x237
        uint8_t strength;                       // 0x238
        uint8_t strength_bonus;                 // 0x239
        uint8_t intelligence;                   // 0x23A
        uint8_t wisdom;                         // 0x23B
        uint8_t dexterity;                      // 0x23C
        uint8_t constitution;                   // 0x23D
        uint8_t charisma;                       // 0x23E
        uint8_t morale;                         // 0x23F
        uint8_t morale_break;                   // 0x240
        uint8_t racial_enemy;                   // 0x241
        uint8_t morale_recovery_time;           // 0x242
        uint32_t kit_id;                        // 0x244
        Resref script_override;                 // 0x0248
        Resref script_class;                    // 0x0250
        Resref script_race;                     // 0x0258
        Resref script_general;                  // 0x0260
        Resref script_default;                  // 0x0268
        uint8_t enemy_ally_id;                  // 0x0270
        uint8_t general_id;                     // 0x0271
        uint8_t race_id;                        // 0x0272
        uint8_t class_id;                       // 0x0273
        uint8_t specific_id;                    // 0x0274
        uint8_t gender_id;                      // 0x0275
        uint8_t object_ids[5];                  // 0x0276
        uint8_t alignment_id;                   // 0x027b
        uint16_t global_actor_id;               // 0x027c
        uint16_t local_actor_id;                // 0x027e
        CharArray<32> death_variable;           // 0x0280
        uint32_t known_spells_offset;           // 0x02a0
        uint32_t known_spells_count;            // 0x02a4
        uint32_t memorization_offset;           // 0x02a8
        uint32_t memorization_count;            // 0x02ac
        uint32_t memorized_offset;              // 0x02b0
        uint32_t memorized_count;               // 0x02b4
        uint32_t item_slots_offset;             // 0x02b8
        uint32_t items_offset;                  // 0x02bc
        uint32_t items_count;                   // 0x02c0
        uint32_t effects_offset;                // 0x02c4
        uint32_t effects_count;                 // 0x02c8
        Resref dialog_file;                     // 0x02cc
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CreKnownSpell
    {
        Resref spell;              // 0x0000
        uint16_t spell_level;      // 0x0008
        uint16_t spell_type;       // 0x000A
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CreSpellMemorizationInfo
    {
        uint16_t spell_level;                 // 0x0000
        uint16_t memorizable;                 // 0x0002
        uint16_t memorizable_after_effects;   // 0x0004
        uint16_t spell_type;                  // 0x0006
        uint32_t index;                       // 0x0008
        uint32_t memorized_count;             // 0x000C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CreSpellMemorizedSpell
    {
        Resref spell;              // 0x0000
        uint32_t memorized;        // 0x0008 bit0: memorized, bit1: disabled
    };
    #pragma pack(pop)
}

#endif