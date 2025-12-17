#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <expected>
#include <string_view>
#include <vector>

#include "cre_file.h"
#include "ie_files.h"
#include "binary_layouts/gam.h"
#include "utils/errors.h"
#include "utils/helper_structs.h"

class GamFile final : public IEFile
{
public:
    [[nodiscard]]
    static Possible<GamFile> open( std::string_view path ) noexcept;
    bool save_gam();

private:
    explicit GamFile( std::string_view path ) noexcept;

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

    void check_for_malformation() noexcept override;
    void prep_containers();
};

#endif // GAM_FILE_H
