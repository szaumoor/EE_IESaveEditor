#ifndef GAM_FILE_H
#define GAM_FILE_H

#include "binary_layouts.h"
#include "cre_file.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <vector>

using std::vector;


class GamFile final : public IEFile
{
public:
    explicit GamFile( const char* path ) noexcept;
    vector<GamCharacterData> party_members;

private:
    GamHeader header;

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
