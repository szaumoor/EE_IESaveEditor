#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <cstdint>
#include <vector>
#include "xref.h"

using std::vector;

namespace
{
    #pragma pack(push, 1)
    struct GamHeader
    {
        CharArray<4> signature;            // 0x0000
        CharArray<4> version;              // 0x0004
        uint32_t game_time;                // 0x0008
        uint16_t selected_formation;       // 0x000C
        uint16_t formations[5];            // 0x000E - 0x0016
        uint32_t party_gold;               // 0x0018
        int16_t active_area_player_id;     // 0x001C
        uint16_t weather_bitfield;         // 0x001E
        uint32_t npc_party_offset;         // 0x0020
        uint32_t npc_party_count;          // 0x0024
        uint32_t party_inv_offset;         // 0x0028
        uint32_t party_inv_count;          // 0x002C
        uint32_t npc_nonparty_offset;      // 0x0030
        uint32_t npc_nonparty_count;       // 0x0034
        uint32_t global_vars_offset;       // 0x0038
        uint32_t global_vars_count;        // 0x003C
        Resref world_area;                 // 0x0040
        uint32_t familiar_extra_offset;    // 0x0048
        uint32_t journal_count;            // 0x004C
        uint32_t journal_offset;           // 0x0050
        uint32_t party_reputation;         // 0x0054
        Resref master_area;                // 0x0058
        uint32_t gui_flags;                // 0x0060
        uint32_t loading_progress;         // 0x0064
        uint32_t familiar_info_offset;     // 0x0068
        uint32_t stored_locs_offset;       // 0x006C
        uint32_t stored_locs_count;        // 0x0070
        uint32_t game_time_real;           // 0x0074
        uint32_t pocket_locs_offset;       // 0x0078
        uint32_t pocket_locs_count;        // 0x007C
        uint32_t zoom_level;               // 0x0080
        Resref rnd_encounter_area;         // 0x0084
        Resref current_campaign;           // 0x008C
        uint32_t familiar_owner;           // 0x0094
        CharArray<20> rnd_encounter_entry; // 0x0098
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamCharacterData
    {
        uint16_t character_selection;            // 0x0000
        uint16_t party_order;                    // 0x0002
        uint32_t cre_offset;                     // 0x0004
        uint32_t cre_size;                       // 0x0008
        CharArray<8> character_name;             // 0x000C
        uint32_t orientation;                    // 0x0014
        Resref current_area;                     // 0x0018
        uint16_t x_coord;                        // 0x0020
        uint16_t y_coord;                        // 0x0022
        uint16_t viewing_rect_x;                 // 0x0024
        uint16_t viewing_rect_y;                 // 0x0026
        uint16_t modal_action;                   // 0x0028
        uint16_t happiness;                      // 0x002A
        uint32_t unused[25];                     // 0x002C – 0x088
        uint16_t quick_weapon_slots[4];          // 0x008C - 0x0092
        uint16_t quick_weapon_abilities[4];      // 0x0094 - 0x009A
        Resref quick_spell_resources[3];         // 0x009C - 0x00AC
        uint16_t quick_spell_slots[3];           // 0x00B4 - 0x00B8
        uint16_t quick_spell_abilities[3];       // 0x00BA - 0x00BE
        CharArray<32> name;                      // 0x00C0
        uint32_t talk_count;                     // 0x00E0
        uint8_t character_stats[116];
        uint8_t voice_set[8];
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamGlobalVariables
    {
        CharArray<32> variable_name;     // 0x0000
        uint16_t type;                   // 0x0020
        uint16_t ref_value;              // 0x0022
        uint32_t dword_value;            // 0x0024
        uint32_t int_value;              // 0x0028
        double double_value;             // 0x002C
        CharArray<32> script_name_value; // 0x0034
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamJournalEntry
    {
        Strref journal_text;             // 0x0000
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
        Resref area;             // 0x0000
        uint16_t x_coord;        // 0x0008
        uint16_t y_coord;        // 0x000A
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
