#include "gam_file.h"
#include "ie_files.h"
#include "utils/helper_structs.h"
#include "utils/io.h"

#include <algorithm>
#include <fstream>
#include <ranges>

using std::string_view;
using std::ifstream;
namespace rng = std::ranges;

static constexpr string_view kGamFileSig("GAME");
static constexpr string_view kGamFileVersion_2_0("V2.0");
static constexpr string_view kGamFileVersion_2_1 ("V2.1");

inline void GamFile::prep_containers()
{
    _party_members.resize( _header.npc_party_count );
    _non_party_members.resize( _header.npc_nonparty_count );
    _variables.resize( _header.global_vars_count );
    _journal_entries.resize( _header.journal_count );
    _stored_locations.resize( _header.stored_locs_count );
    _pocket_plane_info.resize( _header.pocket_locs_count );
    _familiar_extras.resize( 81 );
}

PossibleGamFile GamFile::open(const string_view path) noexcept
{
    ifstream file_handle( path.data(), std::ios::binary );

    if (!file_handle)
        return std::unexpected(IEError(IEErrorType::Unreadable));

    GamFile gam(path);
    auto& header = gam._header;

    const StructWriter writer(file_handle);
    writer.into(header);
    gam.check_for_malformation();

    if (!gam)
        return std::unexpected(IEError(IEErrorType::Malformed));

    gam.prep_containers();

    writer.into(gam._party_members, header.npc_party_offset);
    rng::for_each(gam._party_members, [&](const auto& member) {
        gam._party_cre_files.push_back( std::move(CreFile::read(file_handle, member.cre_offset)) );
    });
    
    writer.into(gam._non_party_members, header.npc_nonparty_offset);
    rng::for_each(gam._non_party_members, [&](const auto& member) {
        gam._non_party_cre_files.push_back( std::move(CreFile::read(file_handle, member.cre_offset )));
    });
    
    writer.into(gam._variables, header.global_vars_offset);
    writer.into(gam._journal_entries, header.journal_offset);
    writer.into(gam._stored_locations, header.stored_locs_offset);
    writer.into(gam._pocket_plane_info, header.pocket_locs_offset);
    writer.into(gam._familiar_info, header.familiar_info_offset);
    writer.into(gam._familiar_extras, header.familiar_extra_offset);

    return std::move(gam);
}

bool GamFile::save_gam()
{
    std::ofstream file_handle(_path.data(), std::ios::binary | std::ios::in | std::ios::out);
    const BinaryWriter writer(file_handle);
    writer.out(_header);
    // rest of details for later
    return true;
}

GamFile::GamFile( const std::string_view path ) noexcept : IEFile( path ) {}

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kGamFileSig;
    const bool valid_version   = _header.version.to_string() == kGamFileVersion_2_0 ||
                                 _header.version.to_string() == kGamFileVersion_2_1;
    
    good = valid_signature && valid_version;
}


