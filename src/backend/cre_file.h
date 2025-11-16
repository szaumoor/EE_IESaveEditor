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
    CreHeader header;

    vector<CreKnownSpell> known_spells;
    vector<CreSpellMemorizationInfo> memorization_infos;
    vector<CreSpellMemorizedSpell> memorized_spells;

    vector<EffectVariant> effects;

    vector<CreInventoryItem> items;
    CreItemSlots item_slots;
};

#endif // CRE_FILE_H