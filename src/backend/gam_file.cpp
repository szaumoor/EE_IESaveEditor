#include "gam_file.h"
#include "ie_files.h"
#include "utils/helper_structs.h"
#include "utils/io.h"

#include <algorithm>
#include <fstream>

using std::string_view;
using std::ifstream;
using std::vector;
using std::string_view;
namespace rng = std::ranges;

static constexpr string_view kGamFileSig( "GAME" );
static constexpr string_view kGamFileVersion_2_0( "V2.0" );
static constexpr string_view kGamFileVersion_2_1( "V2.1" );

Possible<GamFile> GamFile::open( const string_view path ) noexcept
{
    ifstream file_handle( path.data(), std::ios::binary );

    if ( !file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    GamFile gam( path );
    auto& header = gam.m_header;

    const StructWriter writer( file_handle );
    writer.into( header );
    gam.check_for_malformation();

    if ( !gam )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    gam.prep_containers();

    writer.into( gam.m_party_members, header.npc_party_offset );
    rng::for_each( gam.m_party_members, [&]( const auto& member ) {
        gam.m_party_cre_files.push_back( std::move( CreFile::read( file_handle, member.cre_offset ) ) );
    } );

    writer.into( gam.m_non_party_members, header.npc_nonparty_offset );
    rng::for_each( gam.m_non_party_members, [&]( const auto& member ) {
        gam.m_non_party_cre_files.push_back( std::move( CreFile::read( file_handle, member.cre_offset ) ) );
    } );

    writer.into( gam.m_variables, header.global_vars_offset );
    writer.into( gam.m_journal_entries, header.journal_offset );
    writer.into( gam.m_stored_locations, header.stored_locs_offset );
    writer.into( gam.m_pocket_plane_info, header.pocket_locs_offset );
    writer.into( gam.m_familiar_info, header.familiar_info_offset );
    writer.into( gam.m_familiar_extras, header.familiar_extra_offset );

    return std::move( gam );
}

bool GamFile::save_gam()
{
    std::ofstream file_handle( m_path.data(), std::ios::binary | std::ios::in | std::ios::out );
    const BinaryWriter writer( file_handle );
    writer.out( m_header );
    // rest of details for later
    return true;
}

GamFile::GamFile( const std::string_view path ) noexcept : IEFile( path ) { }

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kGamFileSig;
    const bool valid_version   = m_header.version.to_string() == kGamFileVersion_2_0 ||
                               m_header.version.to_string() == kGamFileVersion_2_1;

    m_good = valid_signature && valid_version;
}

inline void GamFile::prep_containers()
{
    m_party_members.resize( m_header.npc_party_count );
    m_non_party_members.resize( m_header.npc_nonparty_count );
    m_variables.resize( m_header.global_vars_count );
    m_journal_entries.resize( m_header.journal_count );
    m_stored_locations.resize( m_header.stored_locs_count );
    m_pocket_plane_info.resize( m_header.pocket_locs_count );
    m_familiar_extras.resize( 81 );
}
