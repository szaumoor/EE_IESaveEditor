#ifndef EE_SAVEEDITOR_RESOURCE_REPOSITORY_H
#define EE_SAVEEDITOR_RESOURCE_REPOSITORY_H

#include <filesystem>
#include <optional>

#include "../../backend/biff_file.hpp"
#include "../../backend/ie_files.hpp"
#include "../../backend/key_file.hpp"
#include "../../backend/tlk_file.hpp"

#include "../profiles/games.hpp"

class ResourceRepository final : public IEClass
{
public:
    [[nodiscard]]
    static Possible<ResourceRepository> open( std::filesystem::path path, Game::Language::Instance lang );

    [[nodiscard]]
    const TlkFile& tlk() const { return m_tlk.value();  }

    [[nodiscard]]
    const KeyFile& key() const { return m_key_file.value(); }

    [[nodiscard]]
    std::span<const BiffFile> bifs() const { return m_bifs; }

    [[nodiscard]]
    bool good() const noexcept { return m_good; }

    explicit operator bool() const noexcept { return m_good; }

private:
    explicit ResourceRepository( std::filesystem::path path);

    std::optional<KeyFile> m_key_file { std::nullopt };
    std::vector<BiffFile> m_bifs;
    std::optional<TlkFile> m_tlk { std::nullopt };

    std::filesystem::path m_root_path;
    bool m_good = true;

    static constexpr std::array<std::string_view, 5> biffs
    {
        "25Items.bif",
        "25Spells.bif",
        "Items.bif",
        "Spells.bif",
        "Patch25.bif"
    };
};


#endif //EE_SAVEEDITOR_RESOURCE_REPOSITORY_H
