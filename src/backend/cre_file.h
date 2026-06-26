#ifndef CRE_FILE_H
#define CRE_FILE_H

#include <ranges>
#include <variant>
#include <vector>

#include "ie_files.h"

#include "binary_layouts/cre.h"
#include "binary_layouts/gam.h"

#include "utils/abstract_structs.h"
#include "utils/aliases.h"
#include "utils/io.h"

class CreFile final
{
public:
    static Possible<CreFile> read( std::ifstream& file, u32 offset );
    std::vector<Effect> effects();

    void check_for_malformation() noexcept;
    [[nodiscard]] bool good() const noexcept { return m_good; }
    explicit operator bool() const noexcept { return m_good;};

    [[nodiscard]]
    auto header() const noexcept { return m_header; }
    [[nodiscard]]
    auto effects() const noexcept { return m_effects; }
    [[nodiscard]]
    auto locals() const noexcept {
        using std::views::transform;
        using std::views::filter;

        auto vars = effects()
            | transform([](auto el){ return std::get<1>(el);})
            | filter([](auto el) { return el.opcode == 187;})
            | transform([](auto el) { return GamLocalVariable(el.variable_name.to_string(), el.parameter1 ); });

        return std::vector(vars.begin(), vars.end());
    }

    [[nodiscard]]
    auto proficiencies() const noexcept
    {
        using std::views::transform;
        using std::views::filter;

        auto vars = effects()
            | transform([](auto el){ return std::get<1>(el);})
            | filter([](auto el) { return el.opcode == 233;})
            | transform([](auto el) {
                return Proficiency(
                    static_cast<u16>(el.parameter2),
                    static_cast<u16>(el.parameter1)
                );
            });

        return std::vector(vars.begin(), vars.end());
    }

private:
    CreHeader m_header{};

    std::vector<CreKnownSpell> m_known_spells;
    std::vector<CreSpellMemorizationInfo> m_memorization_infos;
    std::vector<CreSpellMemorizedSpell> m_memorized_spells;
    std::vector<EffectVariant> m_effects;
    std::vector<CreInventoryItem> m_items;
    CreItemSlots m_item_slots{};

    bool m_good = false;

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
