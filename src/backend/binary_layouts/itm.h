#ifndef EE_SAVEEDITOR_ITM_H
#define EE_SAVEEDITOR_ITM_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#pragma pack(push,1)

struct ItmHeader {
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

static_assert(offsetof(ItmHeader, signature) == 0x0000, "signature offset mismatch");
static_assert(offsetof(ItmHeader, version) == 0x0004, "version offset mismatch");
static_assert(offsetof(ItmHeader, replacement_item) == 0x0010, "replacement item offset mismatch");
static_assert(offsetof(ItmHeader, flags) == 0x0018, "flags offset mismatch");
static_assert(offsetof(ItmHeader, min_level) == 0x0024, "min_level offset mismatch");
static_assert(offsetof(ItmHeader, price) == 0x0034, "price offset mismatch");
static_assert(offsetof(ItmHeader, inventory_icon) == 0x003A, "inventory icon offset mismatch");
static_assert(offsetof(ItmHeader, weight_dword) == 0x004C, "weight offset mismatch");
static_assert(offsetof(ItmHeader, enchantment) == 0x0060, "enchantment offset mismatch");

static_assert(sizeof(ItmHeader) == 100, "itm_header size mismatch");

#endif //EE_SAVEEDITOR_ITM_H