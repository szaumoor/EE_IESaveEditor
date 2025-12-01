#ifndef CRE_FILE_H
#define CRE_FILE_H

#include "utils/aliases.h"
#include "binary_layouts/cre.h"

#include <variant>
#include <vector>

using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;

class CreFile
{
public:
    explicit CreFile( std::ifstream& file, u32 offset ) noexcept;

//private:
    CreHeader _header;

    std::vector<CreKnownSpell> _known_spells;
    std::vector<CreSpellMemorizationInfo> _memorization_infos;
    std::vector<CreSpellMemorizedSpell> _memorized_spells;

    std::vector<EffectVariant> _effects;

    std::vector<CreInventoryItem> _items;
    CreItemSlots _item_slots;
};

#endif // CRE_FILE_H