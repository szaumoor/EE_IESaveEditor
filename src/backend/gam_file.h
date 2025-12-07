#ifndef GAM_FILE_H
#define GAM_FILE_H

#include <expected>
#include <string_view>
#include <vector>

#include "binary_layouts/gam.h"
#include "cre_file.h"
#include "ie_files.h"
#include "utils/helper_structs.h"
#include "utils/errors.h"


class GamFile;

using std::vector;
using std::string_view;
using PossibleGamFile = std::expected<GamFile, IEError>;

class GamFile final : public IEFile
{
public:
    [[nodiscard]]
    static PossibleGamFile open( string_view path ) noexcept;
    bool save_gam();
    GamHeader _header{};
private:
    explicit GamFile( string_view path ) noexcept;



    vector<GamCharacterData> _party_members;
    vector<CreFile> _party_cre_files;
    vector<GamCharacterData> _non_party_members;
    vector<CreFile> _non_party_cre_files;
    vector<GamGlobalVariable> _variables;
    vector<GamJournalEntry> _journal_entries;
    vector<GamLocationInfo> _stored_locations;
    vector<GamLocationInfo> _pocket_plane_info;

    GamFamiliarInfo _familiar_info{};
    vector<Resref> _familiar_extras;

    void check_for_malformation() noexcept override;
    void prep_containers();
};

#endif // GAM_FILE_H
