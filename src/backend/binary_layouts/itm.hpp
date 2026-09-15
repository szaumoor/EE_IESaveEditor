#ifndef EE_SAVEEDITOR_ITM_H
#define EE_SAVEEDITOR_ITM_H

#include "../utils/aliases.hpp"
#include "../utils/helper_structs.hpp"

#include <type_traits>

#pragma pack(push,1)

struct ItmHeader
{
    CharArray<4> signature;
    CharArray<4> version;
    strref unidentified_name;
    strref identified_name;
    CharArray<8> replacement_item;
    u32 flags;
    u16 item_type;
    u8 usability[4];
    CharArray<2> item_animation;
    u16 min_level;
    u16 min_strength;
    u8  min_strength_bonus;
    u8  kit_usability1;
    u8  min_intelligence;
    u8  kit_usability2;
    u8  min_dexterity;
    u8  kit_usability3;
    u8  min_wisdom;
    u8  kit_usability4;
    u8  min_constitution;
    u8  weapon_proficiency;
    u16 min_charisma;
    u32 price;
    u16 stack_amount;
    CharArray<8> inventory_icon;
    u16 lore_to_id;
    CharArray<8> ground_icon;
    u32 weight_dword;
    strref unidentified_desc;
    strref identified_desc;
    CharArray<8> description_icon;
    u32 enchantment;
};
#pragma pack(pop)

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<ItmHeader> );
static_assert( std::is_standard_layout_v<ItmHeader> );
static_assert(sizeof(ItmHeader) == 100, "itm_header size mismatch");

#pragma endregion

#endif //EE_SAVEEDITOR_ITM_H
