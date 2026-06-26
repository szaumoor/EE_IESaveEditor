#ifndef EE_SAVEEDITOR_ABSTRACT_STRUCTS_H
#define EE_SAVEEDITOR_ABSTRACT_STRUCTS_H

#include "aliases.h"

/**
 * Encapsulates a non-legacy proficiency. Non-legacy proficiencies
 * are just instances of effects in a specific creature file, instead
 * of legacy proficiencies which are just a byte in the creature file each.
 * This provides an interface for the data that we care about in those effects
 * that add the proficiency.
 */
struct Proficiency
{
    u16 proficiency;
    u16 pips;

    Proficiency( const u16 prof, const u16 p )
        : proficiency( prof ), pips( p ) { }
};

using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;

/**
 *  This class abstracts away irrelevant info from the possible two variants of the
 *  effect embedded files in the gam files and keeps what matters for the purposes
 *  of the save editor. Since both versions differ quite significantly in presentation
 *  this provides a common interface to access the important data.
 */
class Effect final
{
public:
    static Effect from ( const EmbeddedEffFileV1& eff ) noexcept;
    static Effect from( const EmbeddedEffFileV2& eff ) noexcept;

private:
    Effect() = default;

    template<typename EffectType>
    static constexpr void common_mapping( Effect& effect, EffectType eff )
    {
        static_assert( std::is_same_v<EffectType, EmbeddedEffFileV1> || std::is_same_v<EffectType, EmbeddedEffFileV2> );

        effect.opcode     = eff.opcode;
        effect.duration   = eff.duration;
        effect.parameter1 = eff.parameter1;
        effect.parameter2 = eff.parameter2;
        effect.timing     = eff.timing_mode;
    }

    u32 opcode     = 0;
    u32 timing     = 0;
    u32 duration   = 0;
    i32 parameter1 = 0;
    u32 parameter2 = 0;
    Resref resource{};
};

#endif //EE_SAVEEDITOR_ABSTRACT_STRUCTS_H
