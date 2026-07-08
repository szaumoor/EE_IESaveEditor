#ifndef EE_SAVEEDITOR_SPL_H
#define EE_SAVEEDITOR_SPL_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#include <type_traits>

#pragma pack(push, 1)

struct SplHeader
{
    CharArray<4>  signature;              
    CharArray<4>  version;                
    u32           name_unidentified;       
    u32           name_identified;         
    CharArray<8>  completion_sound;        
    u32           flags;                   
    u16           spell_type;              
    u32           exclusion_flags;         
    u16           casting_graphics;        
    u8            min_level;               
    u8            primary_type;            
    u8            min_strength;            
    u8            secondary_type;          
    u8            min_strength_bonus;      
    u8            usability_1;             
    u8            min_intelligence;        
    u8            usability_2;             
    u8            min_dexterity;           
    u8            usability_3;             
    u8            min_wisdom;              
    u8            usability_4;             
    u16           min_constitution;        
    u16           min_charisma;            
    u32           spell_level;             
    u16           stack_amount;            
    CharArray<8>  spellbook_icon;          
    u16           lore_to_id;               
    CharArray<8>  ground_icon;             
    u32           weight;                  
    u32           desc_unidentified;       
    u32           desc_identified;         
    CharArray<8>  description_icon;        
    u32           enchantment;             
    u32           ext_header_offset;        
    u16           ext_header_count;         
    u32           feature_block_offset;    
    u16           casting_feature_offset;  
    u16           casting_feature_count;   
};

struct SplExtendedHeader
{
    u8   spell_form;                
    u8   flags;                     
    u16  location;                  
    CharArray<8> memorised_icon;    
    u8   target;                    
    u8   target_count;              
    u16  range;                     
    u16  level_required;            
    u16  casting_time;              
    u16  times_per_day;             
    u16  dice_sides;                
    u16  dice_thrown;               
    u16  enchanted;                 
    u16  damage_type;               
    u16  feature_block_count;       
    u16  feature_block_offset;      
    u16  charges;                   
    u16  charge_depletion;          
    u16  projectile;                
};

#pragma pack(pop)

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<SplExtendedHeader> );
static_assert( std::is_standard_layout_v<SplExtendedHeader> );
static_assert(sizeof(SplExtendedHeader) == 0x28, "SplExtendedHeader size mismatch");

static_assert( std::is_trivially_copyable_v<SplHeader> );
static_assert( std::is_standard_layout_v<SplHeader> );
static_assert(sizeof(SplHeader) == 0x72, "SplHeader size mismatch");

#pragma endregion

#endif //EE_SAVEEDITOR_SPL_H
