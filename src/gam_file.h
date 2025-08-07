#ifndef GAM_FILE_H
#define GAM_FILE_H

#include "aliases.h"
#include "helper_structs.h"

#include <vector>

using std::vector;

namespace
{
    #pragma pack(push, 1)
    struct GamHeader
    {
        CharArray<4> signature;            // 0x0000
        CharArray<4> version;              // 0x0004
        u32 game_time;                     // 0x0008
        u16 selected_formation;            // 0x000C
        u16 formations[5];                 // 0x000E - 0x0016
        u32 party_gold;                    // 0x0018
        i16 active_area_player_id;         // 0x001C
        u16 weather_bitfield;              // 0x001E
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
        Resref current_campaign;           // 0x008C
        u32 familiar_owner;                // 0x0094
        CharArray<32> rnd_encounter_entry; // 0x0098
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
        u32 unused[25];                     // 0x002C – 0x088
        u16 quick_weapon_slots[4];          // 0x008C - 0x0092
        u16 quick_weapon_abilities[4];      // 0x0094 - 0x009A
        Resref quick_spell_resources[3];    // 0x009C - 0x00AC
        u16 quick_spell_slots[3];           // 0x00B4 - 0x00B8
        u16 quick_spell_abilities[3];       // 0x00BA - 0x00BE
        CharArray<32> name;                 // 0x00C0
        u32 talk_count;                     // 0x00E0
        u8 character_stats[116];
        u8 voice_set[8];
    };

    struct GamGlobalVariables
    {
        CharArray<32> variable_name;     // 0x0000
        u16 type;                        // 0x0020
        u16 ref_value;                   // 0x0022
        u32 dword_value;                 // 0x0024
        u32 int_value;                   // 0x0028
        double double_value;             // 0x002C
        CharArray<32> script_name_value; // 0x0034
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
        u32 lg_familiar_count[9];           // 0x004C – 0x0068
        u32 ln_familiar_count[9];           // 0x006C – 0x0088
        u32 cg_familiar_count[9];           // 0x008C – 0x00A8
        u32 cn_familiar_count[9];           // 0x0208 – 0x0224
        u32 ng_familiar_count[9];           // 0x011C – 0x0138
        u32 tn_familiar_count[9];           // 0x013C – 0x0158
        u32 ne_familiar_count[9];           // 0x015C – 0x0178
        u32 le_familiar_count[9];           // 0x0184 – 0x0204
        u32 ce_familiar_count[9];           // 0x022C – 0x0248
    };

    struct GamStoredLocationsInfo
    {
        Resref area;        // 0x0000
        u16 x_coord;        // 0x0008
        u16 y_coord;        // 0x000A
    };

    struct GamPocketPlaneInfo
    {
        Resref area;        // 0x0000
        u16 x_coord;        // 0x0008
        u16 y_coord;        // 0x000A
    };
    #pragma pack(pop)
}

class GamFile
{
    GamHeader header;

    vector<GamCharacterData> party_members;
    vector<GamCharacterData> non_party_members;
    vector<GamGlobalVariables> variables;
    vector<GamJournalEntry> journal_entries;
    vector<GamFamiliarInfo> familiar_info;
    vector<GamStoredLocationsInfo> stored_locations;
    vector<GamPocketPlaneInfo> pocket_plane_info;

    explicit GamFile( const char* path );
};

#endif // GAM_FILE_H
