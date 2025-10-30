#ifndef EESAVEEDITORBACKEND_BINARY_LAYOUTS_H
#define EESAVEEDITORBACKEND_BINARY_LAYOUTS_H

#include "aliases.h"
#include "helper_structs.h"

enum ResourceType : u16
{
    NotFound      = 0x0000,
    FileTypeBmp   = 0x0001,
    FileTypeMve   = 0x0002,
    FileTypeWav   = 0x0004,
    FileTypeWfx   = 0x0005,
    FileTypePlt   = 0x0006,
    FileTypeBam   = 0x03e8,
    FileTypeWed   = 0x03e9,
    FileTypeChu   = 0x03ea,
    FileTypeTi    = 0x03eb,
    FileTypeMos   = 0x03ec,
    FileTypeItm   = 0x03ed,
    FileTypeSpl   = 0x03ee,
    FileTypeBcs   = 0x03ef,
    FileTypeIds   = 0x03f0,
    FileTypeCre   = 0x03f1,
    FileTypeAre   = 0x03f2,
    FileTypeDlg   = 0x03f3,
    FileType2da   = 0x03f4,
    FileTypeGam   = 0x03f5,
    FileTypeSto   = 0x03f6,
    FileTypeWmap  = 0x03f7,
    FileTypeChr1  = 0x03f8,
    FileTypeEff   = 0x03f8,
    FileTypeBs    = 0x03f9,
    FileTypeChr   = 0x03fa,
    FileTypeVvc   = 0x03fb,
    FileTypeVef   = 0x03fc,
    FileTypePro   = 0x03fd,
    FileTypeBio   = 0x03fe,
    FileTypeWbm   = 0x03ff,
    FileTypeFnt   = 0x0400,
    FileTypeGui   = 0x0402,
    FileTypeSql   = 0x0403,
    FileTypePvrz  = 0x0404,
    FileTypeGlsl  = 0x0405,
    FileTypeTlk   = 0x0407,
    FileTypeMenu  = 0x0408,
    FileTypeMenu2 = 0x0409,
    FileTypeTtf   = 0x040a,
    FileTypePng   = 0x040b,
    FileTypeBah   = 0x044c,
    FileTypeIni   = 0x0802,
    FileTypeSrc   = 0x0803
};

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
    u8 saving_throw_vs_death;     // 0x54
    u8 saving_throw_vs_wands;     // 0x55
    u8 saving_throw_vs_poly;      // 0x56
    u8 saving_throw_vs_breath;    // 0x57
    u8 saving_throw_vs_spell;     // 0x58
};

struct CreResistances
{
    u8 resist_fire;           // 0x59
    u8 resist_cold;           // 0x5A
    u8 resist_electricity;    // 0x5B
    u8 resist_acid;           // 0x5C
    u8 resist_magic;          // 0x5D
    u8 resist_magic_fire;     // 0x5E
    u8 resist_magic_cold;     // 0x5F
    u8 resist_slashing;       // 0x60
    u8 resist_crushing;       // 0x61
    u8 resist_piercing;       // 0x62
    u8 resist_missile;        // 0x63
};

struct CreLegacyProficiencies
{
    u8 large_sword_proficiency;   // 0x6E
    u8 small_sword_proficiency;   // 0x6F
    u8 bow_proficiency;           // 0x70
    u8 spear_proficiency;         // 0x71
    u8 blunt_proficiency;         // 0x72
    u8 spiked_proficiency;        // 0x73
    u8 axe_proficiency;           // 0x74
    u8 missile_proficiency;       // 0x75
};

struct CreColors
{
    u8 metal_colour_index;     // 0x2C
    u8 minor_colour_index;     // 0x2D
    u8 major_colour_index;     // 0x2E
    u8 skin_colour_index;      // 0x2F
    u8 leather_colour_index;   // 0x30
    u8 armor_colour_index;     // 0x31
    u8 hair_colour_index;      // 0x32
};

struct CreStats
{
    u8 strength;          // 0x238
    u8 strength_bonus;    // 0x239
    u8 intelligence;      // 0x23A
    u8 wisdom;            // 0x23B
    u8 dexterity;         // 0x23C
    u8 constitution;      // 0x23D
    u8 charisma;          // 0x23E
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
    Resref spell;   // 0x0000
    u32 memorized;  // 0x0008 bit0: memorized, bit1: disabled
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

 struct TlkFileHeader
 {
     CharArray<4> signature; // "TLK "
     CharArray<4> version;   // "V1  "
     u16 language_id;
     u32 entry_count;
     u32 offset_to_str_data;
 };

struct TlkFileEntry
{
    u16 entry_flags;
    CharArray<8> resref;
    u32 volume;
    u32 pitch;
    u32 offset_to_string;
    u32 string_length;
};

struct BiffHeader
{
    CharArray<4> signature; // "BIFF"
    CharArray<4> version;   // "V1  "
    u32 count_of_file_entries;
    u32 count_of_tile_entries;
    u32 offset_to_file_entries;
};

struct FileEntry
{
    u32 resource_locator;
    u32 offset;
    u32 size;
    ResourceType resource_type;
    u16 unknown;
};

struct TileEntry
{
    u32 resource_locator;
    u32 offset_resource_data;
    u32 tile_count;
    u32 tile_size;
    ResourceType resource_type;
    u16 unknown;
};

struct GamHeader
{
    CharArray<4> signature;            // 0x0000
    CharArray<4> version;              // 0x0004
    u32 game_time;                     // 0x0008
    u16 selected_formation;            // 0x000C
    u16 formations[5];                 // 0x000E - 0x0016
    u32 party_gold;                    // 0x0018
    i16 active_area_player_id;         // 0x001C
    u16 weather;                       // 0x001E
    u32 npc_party_offset;              // 0x0020
    u32 npc_party_count;               // 0x0024
    u32 party_inv_offset;              // 0x0028
    u32 party_inv_count;               // 0x002C
    u32 npc_nonparty_offset;           // 0x0030
    u32 npc_nonparty_count;            // 0x0034
    u32 global_vars_offset;            // 0x0038
    u32 global_vars_count;             // 0x003C
    Resref world_area;                 // 0x0040
    u32 familiar_extra_offset;         // 0x0048
    u32 journal_count;                 // 0x004C
    u32 journal_offset;                // 0x0050
    u32 party_reputation;              // 0x0054
    Resref master_area;                // 0x0058
    u32 gui_flags;                     // 0x0060
    u32 loading_progress;              // 0x0064
    u32 familiar_info_offset;          // 0x0068
    u32 stored_locs_offset;            // 0x006C
    u32 stored_locs_count;             // 0x0070
    u32 game_time_real;                // 0x0074
    u32 pocket_locs_offset;            // 0x0078
    u32 pocket_locs_count;             // 0x007C
    u32 zoom_level;                    // 0x0080
    Resref rnd_encounter_area;         // 0x0084
    Resref current_worldmap;           // 0x008C
    CharArray<8> current_campaign;     // 0x0094
    u32 familiar_owner;                // 0x009C
    CharArray<20> rnd_encounter_entry; // 0x00A0
};

struct GamCharacterStats
{
    Strref most_powerful_vanquished_name; // 0x0000
    u32 most_powerful_vanquished_xp;      // 0x0004
    u32 time_party_ticks;                 // 0x0008
    u32 time_joined_ticks;                // 0x000C
    u8 in_party;                          // 0x0010 (0 = not in party, 1 = in party)
    u16 unused0;                          // 0x0011
    u8 first_letter_cre_resref;           // 0x0013
    u32 kills_xp_chapter;                 // 0x0014
    u32 kills_number_chapter;             // 0x0018
    u32 kills_xp_total;                   // 0x001C
    u32 kills_number_total;               // 0x0020
    Resref fav_spells[4];                 // 0x0024 - 0x003C
    u16 fav_spells_count[4];              // 0x0044 - 0x004B
    Resref fav_wpns[4];                   // 0x004C - 0x006B
    u16 fav_wpns_count[4];                // 0x006C - 0x0073
};

struct GamCharacterData
{
    u16 character_selection;            // 0x0000
    u16 party_order;                    // 0x0002
    u32 cre_offset;                     // 0x0004
    u32 cre_size;                       // 0x0008
    CharArray<8> character_name;        // 0x000C
    u32 orientation;                    // 0x0014
    Resref current_area;                // 0x0018
    u16 x_coord;                        // 0x0020
    u16 y_coord;                        // 0x0022
    u16 viewing_rect_x;                 // 0x0024
    u16 viewing_rect_y;                 // 0x0026
    u16 modal_action;                   // 0x0028
    u16 happiness;                      // 0x002A
    u32 unused[24];                     // 0x002C � 0x088
    u16 quick_weapon_slots[4];          // 0x008C - 0x0092
    u16 quick_weapon_abilities[4];      // 0x0094 - 0x009A
    Resref quick_spell_resources[3];    // 0x009C - 0x00AC
    u16 quick_spell_slots[3];           // 0x00B4 - 0x00B8
    u16 quick_spell_abilities[3];       // 0x00BA - 0x00BE
    CharArray<32> name;                 // 0x00C0
    u32 talk_count;                     // 0x00E0
    GamCharacterStats character_stats;  // 0x00E4
    CharArray<8> voice_set;             // 0x00158
};

struct GamGlobalVariable
{
    CharArray<32> variable_name; // 0x0000
    u16 type;                    // 0x0020 (b0=int,b1=float,b2=script name,b3=resref,b4=strref,b5=dword)
    u16 unused0;                 // 0x0022
    u32 unused1;                 // 0x0024
    u32 int_value;               // 0x0028
    double unused3;              // 0x002C
    CharArray<32> unused;        // 0x0034
};

struct GamJournalEntry
{
    Strref journal_text;        // 0x0000
    u32 time_seconds;           // 0x0004
    u8 current_chapter;         // 0x0008
    u8 read_by_character;       // 0x0009
    u8 journal_section_flags;   // 0x000A
    u8 location_flag;           // 0x000B
};

struct GamFamiliarInfo
{
    char lawful_good_familiar[8];       // 0x0000
    char lawful_neutral_familiar[8];    // 0x0008
    char lawful_evil_familiar[8];       // 0x0010
    char neutral_good_familiar[8];      // 0x0018
    char neutral_familiar[8];           // 0x0020
    char neutral_evil_familiar[8];      // 0x0028
    char chaotic_good_familiar[8];      // 0x0030
    char chaotic_neutral_familiar[8];   // 0x0038
    char chaotic_evil_familiar[8];      // 0x0040
    u32 familiar_resource_offset;       // 0x0048
    u32 lg_familiar_count[9];           // 0x004C � 0x0068
    u32 ln_familiar_count[9];           // 0x006C � 0x0088
    u32 cg_familiar_count[9];           // 0x008C � 0x00A8
    u32 cn_familiar_count[9];           // 0x0208 � 0x0224
    u32 ng_familiar_count[9];           // 0x011C � 0x0138
    u32 tn_familiar_count[9];           // 0x013C � 0x0158
    u32 ne_familiar_count[9];           // 0x015C � 0x0178
    u32 le_familiar_count[9];           // 0x0184 � 0x0204
    u32 ce_familiar_count[9];           // 0x022C � 0x0248
};

struct GamLocationInfo
{
    Resref area;        // 0x0000
    u16 coords[2];  // 0x0008 - 0x000A
};

struct KeyFileHeader
{
    CharArray<4> signature; // "KEY "
    CharArray<4> version;   // "V1  "
    u32 biff_count;
    u32 resource_count;
    u32 offset_to_biff_entries;
    u32 offset_to_resource_entries;
};

struct BiffEntry
{
    u32 length_biff_file;
    u32 offset_to_biff_filename;
    u16 length_biff_filename_with_null;
    u16 location_file_bitfield;
};

struct ResourceEntry
{
    Resref resource_name;
    u16 resource_type;
    u32 resource_locator;
};

#pragma pack(pop)

#endif //EESAVEEDITORBACKEND_BINARY_LAYOUTS_H