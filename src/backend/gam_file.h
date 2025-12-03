#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <expected>

#include "binary_layouts/gam.h"
#include "cre_file.h"
#include "utils/helper_structs.h"
#include "ie_files.h"

#include <string_view>
#include <vector>

class GamFile;

using PossibleGamFile = std::expected<GamFile, IEError>;

class GamFile final : public IEFile
{
public:
    static PossibleGamFile open(std::string_view path) noexcept;
private:
    explicit GamFile( std::string_view path ) noexcept;
    GamHeader _header{};

    std::vector<GamCharacterData> _party_members;
    std::vector<CreFile> _party_cre_files;
    std::vector<GamCharacterData> _non_party_members;
    std::vector<CreFile> _non_party_cre_files;
    std::vector<GamGlobalVariable> _variables;
    std::vector<GamJournalEntry> _journal_entries;
    std::vector<GamLocationInfo> _stored_locations;
    std::vector<GamLocationInfo> _pocket_plane_info;

    GamFamiliarInfo _familiar_info{};
    std::vector<Resref> _familiar_extras;

    void check_for_malformation() noexcept override;
};

#endif // GAM_FILE_H
