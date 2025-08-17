#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "aliases.h"
#include "eff_files.h"
#include "helper_structs.h"

#include <fstream>
#include <vector>
#include <variant>

using std::vector;
using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;

namespace
{
    #pragma pack(push, 1)
    struct CreArmorClass
    {
        i16 ac_natural;      // 0x46
        i16 ac_effective;    // 0x48
        i16 ac_crushing;     // 0x4A
        i16 ac_missile;      // 0x4C
        i16 ac_piercing;     // 0x4E
        i16 ac_slashing;     // 0x50
    };

    struct CreSavingThrows
    {
        u8 saving_throw_vs_death;          // 0x54
        u8 saving_throw_vs_wands;          // 0x55
        u8 saving_throw_vs_poly;           // 0x56
        u8 saving_throw_vs_breath;         // 0x57
        u8 saving_throw_vs_spell;          // 0x58
    };

    struct CreResistances
    {
        u8 resist_fire;                    // 0x59
        u8 resist_cold;                    // 0x5A
        u8 resist_electricity;             // 0x5B
        u8 resist_acid;                    // 0x5C
        u8 resist_magic;                   // 0x5D
        u8 resist_magic_fire;              // 0x5E
        u8 resist_magic_cold;              // 0x5F
        u8 resist_slashing;                // 0x60
        u8 resist_crushing;                // 0x61
        u8 resist_piercing;                // 0x62
        u8 resist_missile;                 // 0x63
    };

    struct CreLegacyProficiencies
    {
        u8 large_sword_proficiency;        // 0x6E
        u8 small_sword_proficiency;        // 0x6F
        u8 bow_proficiency;                // 0x70
        u8 spear_proficiency;              // 0x71
        u8 blunt_proficiency;              // 0x72
        u8 spiked_proficiency;             // 0x73
        u8 axe_proficiency;                // 0x74
        u8 missile_proficiency;            // 0x75
    };

    struct CreColors
    {
        u8 metal_colour_index;             // 0x2C
        u8 minor_colour_index;             // 0x2D
        u8 major_colour_index;             // 0x2E
        u8 skin_colour_index;              // 0x2F
        u8 leather_colour_index;           // 0x30
        u8 armor_colour_index;             // 0x31
        u8 hair_colour_index;              // 0x32
    };

    struct CreStats
    {
        u8 strength;                       // 0x238
        u8 strength_bonus;                 // 0x239
        u8 intelligence;                   // 0x23A
        u8 wisdom;                         // 0x23B
        u8 dexterity;                      // 0x23C
        u8 constitution;                   // 0x23D
        u8 charisma;                       // 0x23E
    };

    struct CreHeader
    {
        CharArray<4> signature;            // 0x0 "CRE "
        CharArray<4> version;              // 0x4 "V1.0"
        Strref long_name;                  // 0x8
        Strref short_name;                 // 0xC
        u32 cre_flags;                     // 0x10
        u32 xp_gained_kills;               // 0x14
        u32 xp_creature;                   // 0x18
        u32 gold;                          // 0x1C
        u32 permanent_status_flags;        // 0x20
        u16 current_hit_points;            // 0x24
        u16 max_hit_points;                // 0x26
        u32 animation_id;                  // 0x28
        CreColors colors;                  // 0x2C - 0x32
        u8 eff_structure_version;          // 0x33
        Resref small_portrait;             // 0x34
        Resref large_portrait;             // 0x3C
        i8 reputation;                     // 0x44 Minimum value: 0
        u8 hide_in_shadows;                // 0x45
        CreArmorClass armor_class;         // 0x46 - 0x50
        u8 thac0;                          // 0x52
        u8 apr;                            // 0x53
        CreSavingThrows saving_throws;     // 0x54 - 0x58
        CreResistances resistances;        // 0x59 - 0x63
        u8 detect_illusion;                // 0x64
        u8 set_traps;                      // 0x65
        u8 lore;                           // 0x66
        u8 open_locks;                     // 0x67
        u8 move_silently;                  // 0x68
        u8 find_traps;                     // 0x69
        u8 pick_pockets;                   // 0x6A
        u8 fatigue;                        // 0x6B
        u8 intoxication;                   // 0x6C
        u8 luck;                           // 0x6D
        CreLegacyProficiencies profs;      // 0x6E - 0x75
        u8 unused_proficiencies1[5];       // 0x76 - 0x7A
        u8 unused_proficiencies2[7];       // 0x7B - 0x81
        u8 turn_undead_level;              // 0x82
        u8 tracking_level;                 // 0x83
        CharArray<32> tracking_target;     // 0x84
        Strref soundset_strrefs[100];      // 0xA4 - 0x230
        u8 class_levels[3];                // 0x234 - 0x236
        u8 sex;                            // 0x237
        CreStats stats;                    // 0x238 - 0x23E
        u8 morale;                         // 0x23F
        u8 morale_break;                   // 0x240
        u8 racial_enemy;                   // 0x241
        u16 morale_recovery_time;          // 0x242
        u32 kit_id;                        // 0x244
        Resref script_override;            // 0x0248
        Resref script_class;               // 0x0250
        Resref script_race;                // 0x0258
        Resref script_general;             // 0x0260
        Resref script_default;             // 0x0268
        u8 enemy_ally;                     // 0x0270
        u8 general;                        // 0x0271
        u8 race;                           // 0x0272
        u8 clazz;                          // 0x0273
        u8 specific;                       // 0x0274
        u8 gender;                         // 0x0275
        u8 object_ids[5];                  // 0x0276
        u8 alignment;                      // 0x027b
        u16 global_actor_id;               // 0x027c
        u16 local_actor_id;                // 0x027e
        CharArray<32> death_variable;      // 0x0280
        u32 known_spells_offset;           // 0x02a0
        u32 known_spells_count;            // 0x02a4
        u32 memorization_offset;           // 0x02a8
        u32 memorization_count;            // 0x02ac
        u32 memorized_offset;              // 0x02b0
        u32 memorized_count;               // 0x02b4
        u32 item_slots_offset;             // 0x02b8
        u32 items_offset;                  // 0x02bc
        u32 items_count;                   // 0x02c0
        u32 effects_offset;                // 0x02c4
        u32 effects_count;                 // 0x02c8
        Resref dialog_file;                // 0x02cc
    };

    struct CreKnownSpell
    {
        Resref spell;     // 0x0000
        u16 spell_level;  // 0x0008
        u16 spell_type;   // 0x000A
    };

    struct CreSpellMemorizationInfo
    {
        u16 spell_level;                 // 0x0000
        u16 memorizable;                 // 0x0002
        u16 memorizable_after_effects;   // 0x0004
        u16 spell_type;                  // 0x0006
        u32 index;                       // 0x0008
        u32 memorized_count;             // 0x000C
    };

    struct CreSpellMemorizedSpell
    {
        Resref spell;      // 0x0000
        u32 memorized;     // 0x0008 bit0: memorized, bit1: disabled
    };

    struct CreInventoryItem
    {
        Resref item;          // 0x0000
        u8 item_expiration_0; // 0x0008
        u8 item_expiration_1; // 0x0009
        u16 charges[3];       // 0x000A - 0x000E
        u32 flags;            // 0x0010
    };

    struct CreItemSlots
    {
        u16 helmet;                  // 0x0000
        u16 armor;                   // 0x0002
        u16 shield;                  // 0x0004
        u16 gloves;                  // 0x0006
        u16 left_ring;               // 0x0008
        u16 right_ring;              // 0x000A
        u16 amulet;                  // 0x000C
        u16 belt;                    // 0x000E
        u16 boots;                   // 0x0010
        u16 weapon1;                 // 0x0012
        u16 weapon2;                 // 0x0014
        u16 weapon3;                 // 0x0016
        u16 weapon4;                 // 0x0018
        u16 quiver1;                 // 0x001A
        u16 quiver2;                 // 0x001C
        u16 quiver3;                 // 0x001E
        u16 quiver4;                 // 0x0020
        u16 cloak;                   // 0x0022
        u16 quick_item1;             // 0x0024
        u16 quick_item2;             // 0x0026
        u16 quick_item3;             // 0x0028
        u16 inventory[16];           // 0x002A - 0x003A
        u16 magic_weapon;            // 0x003C
        u16 selected_weapon;         // 0x003E
        u16 selected_weapon_ability; // 0x0040
    };

    #pragma pack(pop)
}

struct CreFile
{
    CreHeader header;

    vector<CreKnownSpell> known_spells;
    vector<CreSpellMemorizationInfo> memorization_infos;
    vector<CreSpellMemorizedSpell> memorized_spells;

    vector<EffectVariant> effects;

    vector<CreInventoryItem> items;
    CreItemSlots item_slots;

    explicit CreFile( std::ifstream& file, const u32 offset ) noexcept;
};

#endif