#ifndef EESAVEEDITOR_CRE_H
#define EESAVEEDITOR_CRE_H

#include "../utils/aliases.hpp"
#include "../utils/helper_structs.hpp"

#include <type_traits>

#pragma pack(push, 1)

#pragma region CreSubstructures

struct CreArmorClass
{
    i16 ac_natural;
    i16 ac_effective;
    i16 ac_crushing;
    i16 ac_missile;
    i16 ac_piercing;
    i16 ac_slashing;
};

struct CreSavingThrows
{
    u8 saving_throw_vs_death;
    u8 saving_throw_vs_wands;
    u8 saving_throw_vs_poly;
    u8 saving_throw_vs_breath;
    u8 saving_throw_vs_spell;
};

struct CreResistances
{
    u8 resist_fire;
    u8 resist_cold;
    u8 resist_electricity;
    u8 resist_acid;
    u8 resist_magic;
    u8 resist_magic_fire;
    u8 resist_magic_cold;
    u8 resist_slashing;
    u8 resist_crushing;
    u8 resist_piercing;
    u8 resist_missile;
};

struct CreLegacyProficiencies
{
    u8 large_sword_proficiency;
    u8 small_sword_proficiency;
    u8 bow_proficiency;
    u8 spear_proficiency;
    u8 blunt_proficiency;
    u8 spiked_proficiency;
    u8 axe_proficiency;
    u8 missile_proficiency;
};

struct CreColors
{
    u8 metal_colour_index;
    u8 minor_colour_index;
    u8 major_colour_index;
    u8 skin_colour_index;
    u8 leather_colour_index;
    u8 armor_colour_index;
    u8 hair_colour_index;
};

struct CreStats
{
    u8 strength;
    u8 strength_bonus;
    u8 intelligence;
    u8 wisdom;
    u8 dexterity;
    u8 constitution;
    u8 charisma;
};

#pragma endregion

#pragma region CreTables
struct CreKnownSpell
{
    Resref spell;
    u16 spell_level;
    u16 spell_type;
};

struct CreSpellMemorizationInfo
{
    u16 spell_level;
    u16 memorizable;
    u16 memorizable_after_effects;
    u16 spell_type;
    u32 index;
    u32 memorized_count;
};

struct CreSpellMemorizedSpell
{
    Resref spell;
    u32 memorized;
};

struct CreInventoryItem
{
    Resref item;
    u8 item_expiration_0;
    u8 item_expiration_1;
    u16 charges[3];
    u32 flags;
};

struct CreItemSlots
{
    u16 helmet;
    u16 armor;
    u16 shield;
    u16 gloves;
    u16 left_ring;
    u16 right_ring;
    u16 amulet;
    u16 belt;
    u16 boots;
    u16 weapon1;
    u16 weapon2;
    u16 weapon3;
    u16 weapon4;
    u16 quiver1;
    u16 quiver2;
    u16 quiver3;
    u16 quiver4;
    u16 cloak;
    u16 quick_item1;
    u16 quick_item2;
    u16 quick_item3;
    u16 inventory[16];
    u16 magic_weapon;
    u16 selected_weapon;
    u16 selected_weapon_ability;
};

struct EmbeddedEffFileV1
{
    u16 opcode;
    u8 target;
    u8 power;
    i32 parameter1;
    u32 parameter2;
    u8 timing_mode;
    u8 dispel_resistance;
    u32 duration;
    u8 probabilities[2];
    Resref keyword;
    u32 dice_throw_max_level;
    u32 dice_sides_min_level;
    u32 saving_throw_type;
    u32 saving_throw_bonus;
    u32 special;
};

struct EmbeddedEffFileV2
{
    CharArray<4> signature;
    CharArray<4> version;
    u32 opcode;
    u32 target;
    u32 power;
    i32 parameter1;
    u32 parameter2;
    u32 timing_mode;
    u32 duration;
    u16 probabilities[2];
    Resref resource1;
    u32 dice_thrown;
    u32 dice_sides;
    u32 saving_throw_type;
    u32 saving_throw_bonus;
    u32 special;
    u32 primary_type_school;
    u32 used_internally;
    u32 minimum_level;
    u32 maximum_level;
    u32 dispel_resistance;
    u32 parameter3;
    u32 parameter4;
    u32 parameter5;
    u32 time_applied_ticks;
    Resref resource2;
    Resref resource3;
    u32 caster_location_x;
    u32 caster_location_y;
    u32 target_location_x;
    u32 target_location_y;
    u32 resource_type;
    Resref parent_resource;
    u32 resource_flags;
    u32 impact_projectile;
    u32 source_item_slot;
    CharArray<32> variable_name;
    u32 caster_level;
    u32 internal_flags;
    u32 secondary_type;
    u8 unknown[60];
};
#pragma endregion

struct CreHeader
{
    CharArray<4> signature;
    CharArray<4> version;
    strref long_name;
    strref short_name;
    u32 cre_flags;
    u32 xp_gained_kills;
    u32 xp_creature;
    u32 gold;
    u32 permanent_status_flags;
    u16 current_hit_points;
    u16 max_hit_points;
    u32 animation_id;
    CreColors colors;
    u8 eff_struct_version;
    Resref small_portrait;
    Resref large_portrait;
    i8 reputation;
    u8 hide_in_shadows;
    CreArmorClass armor_class;
    u8 thac0;
    u8 apr;
    CreSavingThrows saving_throws;
    CreResistances resistances;
    u8 detect_illusion;
    u8 set_traps;
    u8 lore;
    u8 open_locks;
    u8 move_silently;
    u8 find_traps;
    u8 pick_pockets;
    u8 fatigue;
    u8 intoxication;
    u8 luck;
    CreLegacyProficiencies profs;
    u8 unused_proficiencies1[5];
    u8 unused_proficiencies2[7];
    u8 turn_undead_level;
    u8 tracking_level;
    CharArray<32> tracking_target;
    strref soundset_strrefs[100];
    u8 class_levels[3];
    u8 sex;
    CreStats stats;
    u8 morale;
    u8 morale_break;
    u8 racial_enemy;
    u16 morale_recovery_time;
    u32 kit_id;
    Resref script_override;
    Resref script_class;
    Resref script_race;
    Resref script_general;
    Resref script_default;
    u8 enemy_ally;
    u8 general;
    u8 race;
    u8 clazz;
    u8 specific;
    u8 gender;
    u8 object_ids[5];
    u8 alignment;
    u16 global_actor_id;
    u16 local_actor_id;
    CharArray<32> death_variable;
    u32 known_spells_offset;
    u32 known_spells_count;
    u32 memorization_offset;
    u32 memorization_count;
    u32 memorized_offset;
    u32 memorized_count;
    u32 item_slots_offset;
    u32 items_offset;
    u32 items_count;
    u32 effects_offset;
    u32 effects_count;
    Resref dialog_file;
};

#pragma pack(pop)

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<CreHeader> );
static_assert( std::is_standard_layout_v<CreHeader> );
static_assert( sizeof( CreHeader ) == 724, "CreHeader size is incorrect" );


static_assert( std::is_trivially_copyable_v<CreArmorClass> );
static_assert( std::is_standard_layout_v<CreArmorClass> );
static_assert( sizeof( CreArmorClass ) == 12, "CreArmorClass size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreSavingThrows> );
static_assert( std::is_standard_layout_v<CreSavingThrows> );
static_assert( sizeof( CreSavingThrows ) == 5, "CreSavingThrows size is incorrect" );


static_assert( std::is_trivially_copyable_v<CreResistances> );
static_assert( std::is_standard_layout_v<CreResistances> );
static_assert( sizeof( CreResistances ) == 11, "CreResistances size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreLegacyProficiencies> );
static_assert( std::is_standard_layout_v<CreLegacyProficiencies> );
static_assert( sizeof( CreLegacyProficiencies ) == 8, "CreLegacyProficiencies size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreColors> );
static_assert( std::is_standard_layout_v<CreColors> );
static_assert( sizeof( CreColors ) == 7, "CreColors size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreStats> );
static_assert( std::is_standard_layout_v<CreStats> );
static_assert( sizeof( CreStats ) == 7, "CreStats size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreKnownSpell> );
static_assert( std::is_standard_layout_v<CreKnownSpell> );
static_assert( sizeof( CreKnownSpell ) == 12, "CreKnownSpell size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreSpellMemorizationInfo> );
static_assert( std::is_standard_layout_v<CreSpellMemorizationInfo> );
static_assert( sizeof( CreSpellMemorizationInfo ) == 16, "CreSpellMemorizationInfo size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreSpellMemorizedSpell> );
static_assert( std::is_standard_layout_v<CreSpellMemorizedSpell> );
static_assert( sizeof( CreSpellMemorizedSpell ) == 12, "CreSpellMemorizedSpell size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreInventoryItem> );
static_assert( std::is_standard_layout_v<CreInventoryItem> );
static_assert( sizeof( CreInventoryItem ) == 20, "CreInventoryItem size is incorrect" );

static_assert( std::is_trivially_copyable_v<CreItemSlots> );
static_assert( std::is_standard_layout_v<CreItemSlots> );
static_assert( sizeof( CreItemSlots ) == 80, "CreItemSlots size is incorrect" );

static_assert( std::is_trivially_copyable_v<EmbeddedEffFileV1> );
static_assert( std::is_standard_layout_v<EmbeddedEffFileV1> );
static_assert( sizeof( EmbeddedEffFileV1 ) == 48, "EmbeddedEffFileV1 size is incorrect" );

static_assert( std::is_trivially_copyable_v<EmbeddedEffFileV2> );
static_assert( std::is_standard_layout_v<EmbeddedEffFileV2> );
static_assert( sizeof( EmbeddedEffFileV2 ) == 264, "EmbeddedEffFileV2 size is incorrect" );

#pragma endregion

#endif //EESAVEEDITOR_CRE_H
