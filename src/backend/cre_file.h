#ifndef CRE_FILE_H
#define CRE_FILE_H


#include "utils/aliases.h"
#include "binary_layouts/cre.h"

#include <optional>
#include <variant>
#include <vector>

#include "utils/errors.h"

class CreFile;

using EffectVariant = std::variant<EmbeddedEffFileV1, EmbeddedEffFileV2>;
using PossibleCre = std::optional<CreFile>;

class CreFile
{
public:
    static CreFile read(std::ifstream& file, u32 offset);

private:
    CreHeader _header{};

    std::vector<CreKnownSpell> _known_spells;
    std::vector<CreSpellMemorizationInfo> _memorization_infos;
    std::vector<CreSpellMemorizedSpell> _memorized_spells;

    std::vector<EffectVariant> _effects; // horrendous

    std::vector<CreInventoryItem> _items;

    CreItemSlots _item_slots{};

    inline void resize_vecs() noexcept;
};

#endif // CRE_FILE_H