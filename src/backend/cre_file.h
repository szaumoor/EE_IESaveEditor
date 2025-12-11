#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "binary_layouts/cre.h"
#include "utils/aliases.h"

#include <variant>
#include <vector>

#include "utils/io.h"

using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;

/**
 *  This class abstracts away irrelevant info from the possible two variants of the
 *  effect embedded files in the gam files and keeps what matters for the purposes
 *  of the save editor. Since both versions differ quite significantly in presentation
 *  this provides a common interface to access the important data.
 */
class Effect
{
public:
    static Effect from( const EmbeddedEffFileV1& eff );
    static Effect from( const EmbeddedEffFileV2& eff );

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
    u32 parameter1 = 0;
    u32 parameter2 = 0;
    Resref resource{};
};

class CreFile
{
public:
    static CreFile read( std::ifstream& file, u32 offset );

    std::vector<Effect> effects();

private:
    CreHeader _header{};

    std::vector<CreKnownSpell> _known_spells;
    std::vector<CreSpellMemorizationInfo> _memorization_infos;
    std::vector<CreSpellMemorizedSpell> _memorized_spells;
    std::vector<EffectVariant> _effects;
    std::vector<CreInventoryItem> _items;

    CreItemSlots _item_slots{};

    inline void resize_vecs() noexcept;

    template<typename T>
    void read_effects(CreFile& cre, const StructWriter& writer)
    {
        std::vector<T> tmp(cre._header.effects_count);
        writer.into(tmp);
        cre._effects.insert(cre._effects.end(), tmp.begin(), tmp.end());
    }
};

#endif // CRE_FILE_H
