#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <string_view>
#include <vector>

#include "cre_file.h"
#include "ie_files.h"
#include "binary_layouts/gam.h"
#include "utils/helper_structs.h"

class GamFile final
{
public:
    static Possible<GamFile> open( std::string_view path );

    [[nodiscard]] bool good() const noexcept { return m_good; }
    [[nodiscard]] std::string_view path() const noexcept { return m_path; }

    explicit operator bool() const noexcept { return m_good; }

    bool save_gam();

    [[nodiscard]]
    auto party_members() const noexcept{ return m_party_members; }

    [[nodiscard]]
    auto& party_members_cre() const noexcept{ return m_party_cre_files; }

    [[nodiscard]]
    auto& header() const noexcept{ return m_header; }

    [[nodiscard]]
    auto& globals() const noexcept{ return m_variables; }

    void check_for_malformation() noexcept;
private:
    explicit GamFile(std::string_view path) : m_path(path) {}

    bool m_good = false;
    std::string m_path;

    GamHeader m_header{};
    std::vector<GamCharacterData> m_party_members;
    std::vector<CreFile> m_party_cre_files;
    std::vector<GamCharacterData> m_non_party_members;
    std::vector<CreFile> m_non_party_cre_files;
    std::vector<GamGlobalVariable> m_variables;
    std::vector<GamJournalEntry> m_journal_entries;
    std::vector<GamLocationInfo> m_stored_locations;
    std::vector<GamLocationInfo> m_pocket_plane_info;

    GamFamiliarInfo m_familiar_info{};
    std::vector<Resref> m_familiar_extras;
    void prep_containers();
};

static_assert(IE_Openable<GamFile>);

#endif // GAM_FILE_H
