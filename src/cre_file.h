#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "aliases.h"
#include "binary_layouts.h"

#include <fstream>
#include <vector>
#include <variant>

using std::vector;
using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;


class CreFile
{
    CreHeader header;

    vector<CreKnownSpell> known_spells;
    vector<CreSpellMemorizationInfo> memorization_infos;
    vector<CreSpellMemorizedSpell> memorized_spells;

    vector<EffectVariant> effects;

    vector<CreInventoryItem> items;
    CreItemSlots item_slots;

public:
    explicit CreFile( std::ifstream& file, u32 offset ) noexcept;
};

#endif // CRE_FILE_H