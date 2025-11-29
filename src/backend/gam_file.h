#ifndef GAM_FILE_H
#define GAM_FILE_H

#include "binary_layouts.h"
#include "cre_file.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <string_view>
#include <vector>

using std::vector;


class GamFile final : public IEFile
{
public:
    explicit GamFile( std::string_view path ) noexcept;

    GamFile() = delete;

    vector<GamCharacterData> _party_members;
    vector<CreFile> _party_cre_files;

private:
    GamHeader _header;

    vector<GamCharacterData> _non_party_members;
    vector<CreFile> _non_party_cre_files;
    vector<GamGlobalVariable> _variables;
    vector<GamJournalEntry> _journal_entries;
    vector<GamLocationInfo> _stored_locations;
    vector<GamLocationInfo> _pocket_plane_info;

    GamFamiliarInfo _familiar_info;
    vector<Resref> _familiar_extras;

    void check_for_malformation() noexcept override;
};

#endif // GAM_FILE_H
