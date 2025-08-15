#ifndef GAM_FILE_H
#define GAM_FILE_H

#include "aliases.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <vector>
#include <iostream>

using std::vector;
using rp::files::IEFile;

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


    void print_gam_header(const GamHeader& header) {
        std::cout << "signature: " << header.signature.to_string() << "\n";
        std::cout << "version: " << header.version.to_string() << "\n";
        std::cout << "game_time: " << header.game_time << "\n";
        std::cout << "selected_formation: " << header.selected_formation << "\n";
        std::cout << "formations: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << header.formations[i];
            if (i < 4) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "party_gold: " << header.party_gold << "\n";
        std::cout << "active_area_player_id: " << header.active_area_player_id << "\n";
        std::cout << "weather: " << header.weather << "\n";
        std::cout << "npc_party_offset: " << header.npc_party_offset << "\n";
        std::cout << "npc_party_count: " << header.npc_party_count << "\n";
        std::cout << "party_inv_offset: " << header.party_inv_offset << "\n";
        std::cout << "party_inv_count: " << header.party_inv_count << "\n";
        std::cout << "npc_nonparty_offset: " << header.npc_nonparty_offset << "\n";
        std::cout << "npc_nonparty_count: " << header.npc_nonparty_count << "\n";
        std::cout << "global_vars_offset: " << header.global_vars_offset << "\n";
        std::cout << "global_vars_count: " << header.global_vars_count << "\n";
        std::cout << "world_area: " << header.world_area.to_string() << "\n";
        std::cout << "familiar_extra_offset: " << header.familiar_extra_offset << "\n";
        std::cout << "journal_count: " << header.journal_count << "\n";
        std::cout << "journal_offset: " << header.journal_offset << "\n";
        std::cout << "party_reputation: " << header.party_reputation << "\n";
        std::cout << "master_area: " << header.master_area.to_string() << "\n";
        std::cout << "gui_flags: " << header.gui_flags << "\n";
        std::cout << "loading_progress: " << header.loading_progress << "\n";
        std::cout << "familiar_info_offset: " << header.familiar_info_offset << "\n";
        std::cout << "stored_locs_offset: " << header.stored_locs_offset << "\n";
        std::cout << "stored_locs_count: " << header.stored_locs_count << "\n";
        std::cout << "game_time_real: " << header.game_time_real << "\n";
        std::cout << "pocket_locs_offset: " << header.pocket_locs_offset << "\n";
        std::cout << "pocket_locs_count: " << header.pocket_locs_count << "\n";
        std::cout << "zoom_level: " << header.zoom_level << "\n";
        std::cout << "rnd_encounter_area: " << header.rnd_encounter_area.to_string() << "\n";
        std::cout << "current_worldmap: " << header.current_worldmap.to_string() << "\n";
        std::cout << "current_campaign: " << header.current_campaign.to_string() << "\n";
        std::cout << "familiar_owner: " << header.familiar_owner << "\n";
        std::cout << "rnd_encounter_entry: " << header.rnd_encounter_entry.to_string() << "\n";
    }
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
        u16 fav_wpns_count[4];                // 0x006C
    };


    void print_gam_character_stats(const GamCharacterStats& stats) {
        std::cout << "most_powerful_vanquished_name: " << stats.most_powerful_vanquished_name.to_string() << "\n";
        std::cout << "most_powerful_vanquished_xp: " << stats.most_powerful_vanquished_xp << "\n";
        std::cout << "time_party_ticks: " << stats.time_party_ticks << "\n";
        std::cout << "time_joined_ticks: " << stats.time_joined_ticks << "\n";
        std::cout << "in_party: " << static_cast<int>(stats.in_party) << "\n";
        std::cout << "unused0: " << stats.unused0 << "\n";
        std::cout << "first_letter_cre_resref: " << static_cast<int>(stats.first_letter_cre_resref) << "\n";
        std::cout << "kills_xp_chapter: " << stats.kills_xp_chapter << "\n";
        std::cout << "kills_number_chapter: " << stats.kills_number_chapter << "\n";
        std::cout << "kills_xp_total: " << stats.kills_xp_total << "\n";
        std::cout << "kills_number_total: " << stats.kills_number_total << "\n";
        std::cout << "fav_spells: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << stats.fav_spells[i].to_string();
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "fav_spells_count: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << stats.fav_spells_count[i];
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "fav_wpns: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << stats.fav_wpns[i].to_string();
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "fav_wpns_count: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << stats.fav_wpns_count[i];
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
    }
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
        u32 unused[24];                     // 0x002C – 0x088
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


    void print_gam_character_data(const GamCharacterData& data) {
        std::cout << "character_selection: " << data.character_selection << "\n";
        std::cout << "party_order: " << data.party_order << "\n";
        std::cout << "cre_offset: " << data.cre_offset << "\n";
        std::cout << "cre_size: " << data.cre_size << "\n";
        std::cout << "character_name: " << data.character_name.to_string() << "\n";
        std::cout << "orientation: " << data.orientation << "\n";
        std::cout << "current_area: " << data.current_area.to_string() << "\n";
        std::cout << "x_coord: " << data.x_coord << "\n";
        std::cout << "y_coord: " << data.y_coord << "\n";
        std::cout << "viewing_rect_x: " << data.viewing_rect_x << "\n";
        std::cout << "viewing_rect_y: " << data.viewing_rect_y << "\n";
        std::cout << "modal_action: " << data.modal_action << "\n";
        std::cout << "happiness: " << data.happiness << "\n";
        std::cout << "unused: ";
        for (int i = 0; i < 24; ++i) {
            std::cout << data.unused[i];
            if (i < 24) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "quick_weapon_slots: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << data.quick_weapon_slots[i];
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "quick_weapon_abilities: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << data.quick_weapon_abilities[i];
            if (i < 3) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "quick_spell_resources: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << data.quick_spell_resources[i].to_string();
            if (i < 2) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "quick_spell_slots: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << data.quick_spell_slots[i];
            if (i < 2) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "quick_spell_abilities: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << data.quick_spell_abilities[i];
            if (i < 2) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "name: " << data.name.to_string() << "\n";
        std::cout << "talk_count: " << data.talk_count << "\n";
        print_gam_character_stats(data.character_stats);
        std::cout << "voice_set: " << data.voice_set.to_string() << "\n";
    }

    struct GamGlobalVariables
    {
        CharArray<32> variable_name; // 0x0000
        u16 type;                    // 0x0020 (b0=int,b1=float,b2=script name,b3=resref,b4=strref,b5=dword)
        u16 unused0;                 // 0x0022
        u32 unused1;                 // 0x0024
        u32 int_value;               // 0x0028
        double unused3;              // 0x002C
        CharArray<32> unused;        // 0x0034
    };

    void print_gam_global_variables(const GamGlobalVariables& var) {
        std::cout << "variable_name: " << var.variable_name.to_string() << "\n";
        std::cout << "type: " << var.type << "\n";
        std::cout << "unused0: " << var.unused0 << "\n";
        std::cout << "unused1: " << var.unused1 << "\n";
        std::cout << "int_value: " << var.int_value << "\n";
        std::cout << "unused3: " << var.unused3 << "\n";
        std::cout << "unused: " << var.unused.to_string() << "\n";
    }

    struct GamJournalEntry
    {
        Strref journal_text;        // 0x0000
        u32 time_seconds;           // 0x0004
        u8 current_chapter;         // 0x0008
        u8 read_by_character;       // 0x0009
        u8 journal_section_flags;   // 0x000A
        u8 location_flag;           // 0x000B
    };

    void print_gam_journal_entry(const GamJournalEntry& entry) {
        std::cout << "journal_text: " << entry.journal_text.to_string() << "\n";
        std::cout << "time_seconds: " << entry.time_seconds << "\n";
        std::cout << "current_chapter: " << static_cast<int>(entry.current_chapter) << "\n";
        std::cout << "read_by_character: " << static_cast<int>(entry.read_by_character) << "\n";
        std::cout << "journal_section_flags: " << static_cast<int>(entry.journal_section_flags) << "\n";
        std::cout << "location_flag: " << static_cast<int>(entry.location_flag) << "\n";
    }

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
    void print_gam_familiar_info( const GamFamiliarInfo& info ) {
        std::cout << "lawful_good_familiar: " << info.lawful_good_familiar << "\n";
        std::cout << "lawful_neutral_familiar: " << info.lawful_neutral_familiar << "\n";
        std::cout << "lawful_evil_familiar: " << info.lawful_evil_familiar << "\n";
        std::cout << "neutral_good_familiar: " << info.neutral_good_familiar << "\n";
        std::cout << "neutral_familiar: " << info.neutral_familiar << "\n";
        std::cout << "neutral_evil_familiar: " << info.neutral_evil_familiar << "\n";
        std::cout << "chaotic_good_familiar: " << info.chaotic_good_familiar << "\n";
        std::cout << "chaotic_neutral_familiar: " << info.chaotic_neutral_familiar << "\n";
        std::cout << "chaotic_evil_familiar: " << info.chaotic_evil_familiar << "\n";
        std::cout << "familiar_resource_offset: " << info.familiar_resource_offset << "\n";
        std::cout << "lg_familiar_count: ";
        for ( int i = 0; i < 9; ++i ) {
            std::cout << info.lg_familiar_count[i];
            if ( i < 8 ) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "ln_familiar_count: ";
        for ( int i = 0; i < 9; ++i ) {
            std::cout << info.ln_familiar_count[i];
            if ( i < 8 ) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "cg_familiar_count: ";
        for ( int i = 0; i < 9; ++i ) {
            std::cout << info.cg_familiar_count[i];
            if ( i < 8 ) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "cn_familiar_count: ";
        for ( int i = 0; i < 9; ++i ) {
            std::cout << "cn_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.cn_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
            std::cout << "ng_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.ng_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
            std::cout << "tn_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.tn_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
            std::cout << "ne_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.ne_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
            std::cout << "le_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.le_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
            std::cout << "ce_familiar_count: ";
            for ( int i = 0; i < 9; ++i ) {
                std::cout << info.ce_familiar_count[i];
                if ( i < 8 ) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }

    struct GamLocationInfo
    {
        Resref area;        // 0x0000
        u16 coords[2];  // 0x0008 - 0x000A
    };

    void print_gam_location_info(const GamLocationInfo& loc) {
        std::cout << "area: " << loc.area.to_string() << "\n";
        std::cout << "coords: (" << loc.coords[0] << ", " << loc.coords[1] << ")\n";
    }
    #pragma pack(pop)
}

class GamFile : public IEFile
{
private:
    GamHeader header;
    vector<GamCharacterData> party_members;
    vector<GamCharacterData> non_party_members;
    vector<GamCharacterStats> character_stats;
    vector<GamGlobalVariables> variables;
    vector<GamJournalEntry> journal_entries;
    vector<GamLocationInfo> stored_locations;
    vector<GamLocationInfo> pocket_plane_info;
    GamFamiliarInfo familiar_info;
    vector<Resref> familiar_extras;
public:
    explicit GamFile( const char* path );
    void check_for_malformation() noexcept override;
};

#endif // GAM_FILE_H
