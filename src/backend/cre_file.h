#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "aliases.h"
#include "binary_layouts.h"

#include <variant>
#include <vector>

using std::vector;
using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;


class CreFile
{
public:
    explicit CreFile( std::ifstream& file, u32 offset ) noexcept;

//private:
    CreHeader _header;

    vector<CreKnownSpell> _known_spells;
    vector<CreSpellMemorizationInfo> _memorization_infos;
    vector<CreSpellMemorizedSpell> _memorized_spells;

    vector<EffectVariant> _effects;

    vector<CreInventoryItem> _items;
    CreItemSlots _item_slots;
};

#endif // CRE_FILE_H