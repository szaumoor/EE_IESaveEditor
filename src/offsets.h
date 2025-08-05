#ifndef OFFSETS_H
#define OFFSETS_H

#include <cstdint>

namespace offsets
{
    namespace gam
    {
        constexpr uint32_t global_var_bytes        { 0x54  };
        constexpr uint32_t global_vars_number      { 0x3c  };
        constexpr uint32_t global_vars_offset      { 0x38  };
        constexpr uint32_t journal_entries_number  { 0x4c  };
        constexpr uint32_t journal_entries_offset  { 0x50  };
        constexpr uint32_t party_gold              { 0x18  };
        constexpr uint32_t party_members           { 0x24  };
        constexpr uint32_t party_member_bytes      { 0x160 };
        constexpr uint32_t party_members_offset    { 0x20  };
        constexpr uint32_t reputation              { 0x54  };
        constexpr uint32_t time_seconds            { 0x08  };
        constexpr uint32_t time_ticks              { 0x74  };
    }

    namespace pmember
    {
        constexpr uint32_t creature_offset         { 0x04  };
        constexpr uint32_t join_time_ticks         { 0xf0  };
        constexpr uint32_t kills_xp_chapter        { 0xf8  };
        constexpr uint32_t kills_chapter           { 0xfc  };
        constexpr uint32_t kills_xp_game           { 0x100 };
        constexpr uint32_t kills_game              { 0x104 };
        constexpr uint32_t most_powerful_killed    { 0xe4  };
        constexpr uint32_t pc_name                 { 0xc0  };
        constexpr uint32_t time_in_party_ticks     { 0xec  };
        constexpr uint32_t xp_most_powerful        { 0xe8  };
        constexpr uint32_t favorite_spell_1        { 0x108 };
        constexpr uint32_t favorite_weapon         { 0x130 };
    }

    namespace cre
    {
        namespace eff
        {
            constexpr uint32_t opcode              { 0x08 };
            constexpr uint32_t parameter_one       { 0x14 };
            constexpr uint32_t parameter_two       { 0x18 };
            constexpr uint32_t timing              { 0x1c };
            constexpr uint32_t variable_name       { 0xa0 };
        }

        constexpr uint32_t name                    { 0x8 };
        constexpr uint32_t current_hp              { 0x24 };
        constexpr uint32_t max_hp                  { 0x26 };
        constexpr uint32_t flags                   { 0x10 };

        constexpr uint32_t fire_resist             { 0x59 };
        constexpr uint32_t cold_resist             { 0x5a };
        constexpr uint32_t electric_resist         { 0x5b };
        constexpr uint32_t acid_resist             { 0x5c };
        constexpr uint32_t magic_resist            { 0x5d };
        constexpr uint32_t magic_fire_resist       { 0x5e };
        constexpr uint32_t magic_cold_resist       { 0x5f };

        constexpr uint32_t slashing_resistance     { 0x60 };
        constexpr uint32_t crushing_resistance     { 0x61 };
        constexpr uint32_t piercing_resistance     { 0x62 };
        constexpr uint32_t missile_resistance      { 0x63 };

        constexpr uint32_t hide_in_shadows         { 0x45 };
        constexpr uint32_t set_traps               { 0x65 };
        constexpr uint32_t detect_illusions        { 0x64 };
        constexpr uint32_t open_locks              { 0x67 };
        constexpr uint32_t move_silently           { 0x68 };
        constexpr uint32_t find_traps              { 0x69 };
        constexpr uint32_t pick_pockets            { 0x6a };

        constexpr uint32_t lore                    { 0x66 };

        constexpr uint32_t save_death              { 0x54 };
        constexpr uint32_t save_wand               { 0x55 };
        constexpr uint32_t save_polymorph          { 0x56 };
        constexpr uint32_t save_breath             { 0x57 };
        constexpr uint32_t save_spell              { 0x58 };

        constexpr uint32_t natural_ac              { 0x46 };
        constexpr uint32_t effective_ac            { 0x48 };
        constexpr uint32_t crushing_modifier       { 0x4a };
        constexpr uint32_t missile_modifier        { 0x4c };
        constexpr uint32_t piercing_modifier       { 0x4e };
        constexpr uint32_t slashing_modifier       { 0x50 };

        constexpr uint32_t thac0                   { 0x52 };
        constexpr uint32_t apr                     { 0x53 };

        constexpr uint32_t fatigue                 { 0x6b };
        constexpr uint32_t intoxication            { 0x6c };
        constexpr uint32_t luck                    { 0x6d };

        constexpr uint32_t level_first_class       { 0x234 };
        constexpr uint32_t level_second_class      { 0x235 };
        constexpr uint32_t level_third_class       { 0x236 };

        constexpr uint32_t sex                     { 0x237 };

        constexpr uint32_t strength                { 0x238 };
        constexpr uint32_t strength_bonus          { 0x239 };
        constexpr uint32_t intelligence            { 0x23a };
        constexpr uint32_t wisdom                  { 0x23b };
        constexpr uint32_t dexterity               { 0x23c };
        constexpr uint32_t constitution            { 0x23d };
        constexpr uint32_t charisma                { 0x23e };

        constexpr uint32_t morale                  { 0x23f };
        constexpr uint32_t morale_break            { 0x240 };
        constexpr uint32_t morale_recovery         { 0x242 };

        constexpr uint32_t racial_enemy            { 0x241 };

        constexpr uint32_t race                    { 0x272 };
        constexpr uint32_t class_                  { 0x273 };
        constexpr uint32_t kit                     { 0x244 };
        constexpr uint32_t gender                  { 0x275 };

        constexpr uint32_t alignment               { 0x27b };

        constexpr uint32_t status                  { 0x20 };
        constexpr uint32_t animation               { 0x28 };

        constexpr uint32_t effects_offset          { 0x2c4 };
        constexpr uint32_t effects_number          { 0x2c8 };
        constexpr uint32_t effects_bytes           { 0x108 };

        constexpr uint32_t turn_undead             { 0x82 };

        constexpr uint32_t xp                      { 0x18 };

        constexpr uint32_t known_spells_offset     { 0x2a0 };
        constexpr uint32_t known_spells_number     { 0x2a4 };
        constexpr uint32_t known_spell_bytes       { 0xc   };

        constexpr uint32_t memorization_info_offset{ 0x2a8 };
        constexpr uint32_t memorization_info_number{ 0x2ac };
        constexpr uint32_t memorization_info_bytes { 0x10  };

        constexpr uint32_t memorized_spells_offset { 0x2b0 };
        constexpr uint32_t memorized_spells_number { 0x2b4 };

        constexpr uint32_t item_slots_offset       { 0x2b8 };
        constexpr uint32_t item_slots_bytes        { 0x2   };

        constexpr uint32_t items_offset            { 0x2bc };
        constexpr uint32_t items_number            { 0x2c0 };
        constexpr uint32_t items_bytes             { 0x14  };

        constexpr uint32_t large_swords_prof       { 0x6e };
        constexpr uint32_t small_swords_prof       { 0x6f };
        constexpr uint32_t bows_prof               { 0x70 };
        constexpr uint32_t spears_prof             { 0x71 };
        constexpr uint32_t blunt_prof              { 0x72 };
        constexpr uint32_t spiked_prof             { 0x73 };
        constexpr uint32_t axes_prof               { 0x74 };
        constexpr uint32_t missile_prof            { 0x75 };
    }

    namespace global
    {
        constexpr uint32_t value                   { 0x28 };
    }

    namespace memorization_info
    {
        constexpr uint32_t memorizable             { 0x2 };
        constexpr uint32_t memorizable_now         { 0x4 };
        constexpr uint32_t type                    { 0x6 };
        constexpr uint32_t spell_table_index       { 0x8 };
        constexpr uint32_t spell_count             { 0xc };
    }

    namespace memorized_spell
    {
        constexpr uint32_t memorization            { 0x2 };
        constexpr uint32_t unknown                 { 0x4 };
    }

    namespace known_spell
    {
        constexpr uint32_t level                   { 0x8 };
        constexpr uint32_t type                    { 0xa };
    }
}
#endif // OFFSETS_H
