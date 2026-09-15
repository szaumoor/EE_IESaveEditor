#ifndef EESAVEEDITOR_GAM_H
#define EESAVEEDITOR_GAM_H

#include "../utils/aliases.hpp"
#include "../utils/helper_structs.hpp"

#include <type_traits>

#pragma pack(push, 1)

struct GamHeader
{
    CharArray<4> signature;
    CharArray<4> version;
    u32 game_time;
    u16 selected_formation;
    u16 formations[5];
    u32 party_gold;
    i16 active_area_player_id;
    u16 weather;
    u32 npc_party_offset;
    u32 npc_party_count;
    u32 party_inv_offset;
    u32 party_inv_count;
    u32 npc_nonparty_offset;
    u32 npc_nonparty_count;
    u32 global_vars_offset;
    u32 global_vars_count;
    Resref world_area;
    u32 familiar_extra_offset;
    u32 journal_count;
    u32 journal_offset;
    u32 party_reputation;
    Resref master_area;
    u32 gui_flags;
    u32 loading_progress;
    u32 familiar_info_offset;
    u32 stored_locs_offset;
    u32 stored_locs_count;
    u32 game_time_real;
    u32 pocket_locs_offset;
    u32 pocket_locs_count;
    u32 zoom_level;
    Resref rnd_encounter_area;
    Resref current_worldmap;
    CharArray<8> current_campaign;
    u32 familiar_owner;
    CharArray<20> rnd_encounter_entry;
};

struct GamCharacterStats
{
    strref most_powerful_vanquished_name;
    u32 most_powerful_vanquished_xp;
    u32 time_party_ticks;
    u32 time_joined_ticks;
    u8 in_party;
    u16 unused0;
    u8 first_letter_cre_resref;
    u32 kills_xp_chapter;
    u32 kills_number_chapter;
    u32 kills_xp_total;
    u32 kills_number_total;
    Resref fav_spells[4];
    u16 fav_spells_count[4];
    Resref fav_wpns[4];
    u16 fav_wpns_count[4];
};

struct GamCharacterData
{
    u16 character_selection;
    u16 party_order;
    u32 cre_offset;
    u32 cre_size;
    CharArray<8> character_name;
    u32 orientation;
    Resref current_area;
    u16 x_coord;
    u16 y_coord;
    u16 viewing_rect_x;
    u16 viewing_rect_y;
    u16 modal_action;
    u16 happiness;
    u32 unused[24];
    u16 quick_weapon_slots[4];
    u16 quick_weapon_abilities[4];
    Resref quick_spell_resources[3];
    u16 quick_spell_slots[3];
    u16 quick_spell_abilities[3];
    CharArray<32> name;
    u32 talk_count;
    GamCharacterStats character_stats;
    CharArray<8> voice_set;
};

struct GamGlobalVariable
{
    CharArray<32> variable_name = {};
    u16 type = 0;
    u16 unused0 = 0;
    u32 unused1 = 0;
    i32 int_value = 0;
    double unused3 = 0.0;
    CharArray<32> unused = {};

    GamGlobalVariable() = default;

    GamGlobalVariable(const std::string& name, const i32 value)
    {
        variable_name.assign_string( name );
        int_value = value;
    }
};

using GamLocalVariable = GamGlobalVariable;

struct GamJournalEntry
{
    strref journal_text;
    u32 time_seconds;
    u8 current_chapter;
    u8 read_by_character;
    u8 journal_section_flags;
    u8 location_flag;
};

struct GamFamiliarInfo
{
    char lawful_good_familiar[8];
    char lawful_neutral_familiar[8];
    char lawful_evil_familiar[8];
    char neutral_good_familiar[8];
    char neutral_familiar[8];
    char neutral_evil_familiar[8];
    char chaotic_good_familiar[8];
    char chaotic_neutral_familiar[8];
    char chaotic_evil_familiar[8];
    u32 familiar_resource_offset;
    u32 lg_familiar_count[9];
    u32 ln_familiar_count[9];
    u32 cg_familiar_count[9];
    u32 cn_familiar_count[9];
    u32 ng_familiar_count[9];
    u32 tn_familiar_count[9];
    u32 ne_familiar_count[9];
    u32 le_familiar_count[9];
    u32 ce_familiar_count[9];
};

struct GamLocationInfo
{
    Resref area;
    u16 coords[2];
};

#pragma pack(pop)

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<GamCharacterStats> );
static_assert( std::is_standard_layout_v<GamCharacterStats> );
static_assert( sizeof( GamCharacterStats ) == 116, "GamCharacterStats size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamHeader> );
static_assert( std::is_standard_layout_v<GamHeader> );
static_assert( sizeof( GamHeader )         == 180, "GamHeader size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamCharacterData> );
static_assert( std::is_standard_layout_v<GamCharacterData> );
static_assert( sizeof( GamCharacterData )  == 352, "GamCharacterData size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamGlobalVariable> );
static_assert( std::is_standard_layout_v<GamGlobalVariable> );
static_assert( sizeof( GamGlobalVariable ) == 84, "GamGlobalVariable size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamJournalEntry> );
static_assert( std::is_standard_layout_v<GamJournalEntry> );
static_assert( sizeof( GamJournalEntry )   == 12, "GamJournalEntry size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamFamiliarInfo> );
static_assert( std::is_standard_layout_v<GamFamiliarInfo> );
static_assert( sizeof( GamFamiliarInfo )   == 400, "GamFamiliarInfo size is incorrect" );

static_assert( std::is_trivially_copyable_v<GamLocationInfo> );
static_assert( std::is_standard_layout_v<GamLocationInfo> );
static_assert( sizeof( GamLocationInfo )   == 12, "GamLocationInfo size is incorrect" );

#pragma endregion

#endif //EESAVEEDITOR_GAM_H
