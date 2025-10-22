#ifndef GAM_FILE_H
#define GAM_FILE_H

#include "cre_file.h"
#include "helper_structs.h"
#include "ie_files.h"
#include "binary_layouts.h"

#include <vector>

using std::vector;
using rp::files::IEFile;


class GamFile final : public IEFile
{
public:
    explicit GamFile( const char* path ) noexcept;
private:
    GamHeader header;

    vector<GamCharacterData> party_members;
    vector<GamCharacterData> non_party_members;
    vector<CreFile> party_cre_files;
    vector<CreFile> non_party_cre_files;

    vector<GamCharacterStats> character_stats;

    vector<GamGlobalVariable> variables;

    vector<GamJournalEntry> journal_entries;

    vector<GamLocationInfo> stored_locations;
    vector<GamLocationInfo> pocket_plane_info;

    GamFamiliarInfo familiar_info;
    vector<Resref> familiar_extras;

    void check_for_malformation() noexcept override;
};

#endif // GAM_FILE_H
