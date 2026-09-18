#ifndef CRE_FILE_H
#define CRE_FILE_H

#include <variant>
#include <vector>

#include "ie_files.hpp"

#include "binary_layouts/cre.hpp"
#include "binary_layouts/gam.hpp"

#include "utils/abstract_structs.hpp"
#include "utils/aliases.hpp"
#include "utils/io.hpp"

class CreFile final : public IEClass
{
public:
    static Possible<CreFile> read( std::ifstream& file, u32 offset );
    std::vector<Effect> effects(); // shouldn't be public, it's here because of testing

    void check_for_malformation() noexcept;
    [[nodiscard]] bool good() const noexcept { return m_good; }
    explicit operator bool() const noexcept { return m_good; }

    [[nodiscard]]
    auto& header() const noexcept { return m_header; }
    [[nodiscard]]
    auto effects() const noexcept { return m_effects; }
    [[nodiscard]]
    std::vector<GamGlobalVariable> locals() const noexcept;

    [[nodiscard]]
    std::vector<Proficiency> proficiencies() const noexcept;

private:
    CreHeader m_header {};
    bool m_good { false };

    std::vector<CreKnownSpell> m_known_spells;
    std::vector<CreSpellMemorizationInfo> m_memorization_infos;
    std::vector<CreSpellMemorizedSpell> m_memorized_spells;
    std::vector<EffectVariant> m_effects;
    std::vector<CreInventoryItem> m_items;
    CreItemSlots m_item_slots{};

    inline void resize_vecs() noexcept;

    template<typename T>
    void read_effects( CreFile& cre, const StructWriter& writer )
    {
        static_assert(std::is_same_v<T, EmbeddedEffFileV1> || std::is_same_v<T, EmbeddedEffFileV2>);

        std::vector<T> tmp( cre.m_header.effects_count );
        writer.into( tmp );
        cre.m_effects.insert( cre.m_effects.end(), tmp.begin(), tmp.end() );
    }
};

static_assert(IE_Readable<CreFile>);

#endif // CRE_FILE_H
