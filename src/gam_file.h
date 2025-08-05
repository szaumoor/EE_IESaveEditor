#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <cstdint>
#include <vector>

using std::vector;

namespace
{
    #pragma pack(push, 1)
    struct GamHeader
    {
        char signature[4];               // 0x0000
        char version[4];                 // 0x0004
        uint32_t game_time;              // 0x0008
        uint16_t selected_formation;     // 0x000C
        uint16_t formation_1;            // 0x000E
        uint16_t formation_2;            // 0x0010
        uint16_t formation_3;            // 0x0012
        uint16_t formation_4;            // 0x0014
        uint16_t formation_5;            // 0x0016
        uint32_t party_gold;             // 0x0018
        int16_t active_area_player_id;   // 0x001C
        uint16_t weather_bitfield;       // 0x001E
        uint32_t npc_party_offset;       // 0x0020
        uint32_t npc_party_count;        // 0x0024
        uint32_t party_inv_offset;       // 0x0028
        uint32_t party_inv_count;        // 0x002C
        uint32_t npc_nonparty_offset;    // 0x0030
        uint32_t npc_nonparty_count;     // 0x0034
        uint32_t global_vars_offset;     // 0x0038
        uint32_t global_vars_count;      // 0x003C
        char main_area[8];               // 0x0040
        uint32_t familiar_extra_offset;  // 0x0048
        uint32_t journal_count;          // 0x004C
        uint32_t journal_offset;         // 0x0050
        uint32_t party_reputation;       // 0x0054
        char current_area[8];            // 0x0058
        uint32_t gui_flags;              // 0x0060
        uint32_t loading_progress;       // 0x0064
        uint32_t familiar_info_offset;   // 0x0068
        uint32_t stored_locs_offset;     // 0x006C
        uint32_t stored_locs_count;      // 0x0070
        uint32_t game_time_real;         // 0x0074
        uint32_t pocket_locs_offset;     // 0x0078
        uint32_t pocket_locs_count;      // 0x007C
        uint32_t zoom_level;             // 0x0080
        char rnd_encounter_area[8];      // 0x0084
        char current_campaign[8];        // 0x008C
        uint32_t familiar_owner;         // 0x0094
        char rnd_encounter_entry[20];    // 0x0098
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamCharacterData
    {
        uint16_t character_selection;
        uint16_t party_order;
        uint32_t cre_offset;
        uint32_t cre_size;
        char character_name[8];
        uint32_t orientation;
        char current_area[8];
        uint16_t x_coord;
        uint16_t y_coord;
        uint16_t viewing_rect_x;
        uint16_t viewing_rect_y;
        uint16_t modal_action;
        uint16_t happiness;
        uint32_t interacted_npc_count[24];
        uint16_t quick_weapon_slot_1;
        uint16_t quick_weapon_slot_2;
        uint16_t quick_weapon_slot_3;
        uint16_t quick_weapon_slot_4;
        uint16_t quick_weapon_ability_1;
        uint16_t quick_weapon_ability_2;
        uint16_t quick_weapon_ability_3;
        uint16_t quick_weapon_ability_4;
        char quick_spell_resource_1[8];
        char quick_spell_resource_2[8];
        char quick_spell_resource_3[8];
        uint16_t quick_item_slot_1;
        uint16_t quick_item_slot_2;
        uint16_t quick_item_slot_3;
        uint16_t quick_item_ability_1;
        uint16_t quick_item_ability_2;
        uint16_t quick_item_ability_3;
        char name[32];
        uint32_t talk_count;
        uint8_t character_stats[116];
        uint8_t voice_set[8];
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamGlobalVariables
    {
        char variable_name[32];     // 0x0000
        uint16_t type;              // 0x0020
        uint16_t ref_value;         // 0x0022
        uint32_t dword_value;       // 0x0024
        uint32_t int_value;         // 0x0028
        double double_value;        // 0x002C
        char script_name_value[32]; // 0x0034
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamJournalEntry
    {
        uint32_t journal_text_strref;    // 0x0000
        uint32_t time_seconds;           // 0x0004
        uint8_t current_chapter;         // 0x0008
        uint8_t read_by_character;       // 0x0009
        uint8_t journal_section_flags;   // 0x000A
        uint8_t location_flag;           // 0x000B
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
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
        uint32_t familiar_resource_offset;  // 0x0048
        uint32_t lg_familiar_count[9];      // 0x004C – 0x0068
        uint32_t ln_familiar_count[9];      // 0x006C – 0x0088
        uint32_t cg_familiar_count[9];      // 0x008C – 0x00A8
        uint32_t cn_familiar_count[9];      // 0x0208 – 0x0224
        uint32_t ng_familiar_count[9];      // 0x011C – 0x0138
        uint32_t tn_familiar_count[9];      // 0x013C – 0x0158
        uint32_t ne_familiar_count[9];      // 0x015C – 0x0178
        uint32_t le_familiar_count[9];      // 0x0184 – 0x0204
        uint32_t ce_familiar_count[9];      // 0x022C – 0x0248
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamStoredLocationsInfo
    {
        char area[8];            // 0x0000
        uint16_t x_coord;        // 0x0008
        uint16_t y_coord;        // 0x000A
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamPocketPlaneInfo
    {
        char area[8];            // 0x0000
        uint16_t x_coord;        // 0x0008
        uint16_t y_coord;        // 0x000A
    };
    #pragma pack(pop)

    struct 
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
