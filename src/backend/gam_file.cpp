#include "gam_file.h"
#include "utils/helper_structs.h"
#include "ie_files.h"

#include <fstream>

static constexpr std::string_view kGamFileSig("GAME");
static constexpr std::string_view kGamFileVersion_2_0("V2.0");
static constexpr std::string_view kGamFileVersion_2_1 ("V2.1");

PossibleGamFile GamFile::open(const std::string_view path) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );

    if (!file_handle)
        return std::unexpected(IEError(IEErrorType::Unreadable, "Could not read the GAM file"));

    GamFile gam(path);
    file_handle.read( reinterpret_cast<char*>(&gam._header), sizeof( GamHeader ) );
    gam.check_for_malformation();

    if (!gam)
        return std::unexpected(IEError(IEErrorType::Malformed, "GAM file has the wrong signature or is corrupted"));

    gam._party_members.resize( gam._header.npc_party_count );
    gam._non_party_members.resize( gam._header.npc_nonparty_count );
    gam._variables.resize( gam._header.global_vars_count );
    gam._journal_entries.resize( gam._header.journal_count );
    gam._stored_locations.resize( gam._header.stored_locs_count );
    gam._pocket_plane_info.resize( gam._header.pocket_locs_count );
    gam._familiar_extras.resize( 81 );

    file_handle.seekg( gam._header.npc_party_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._party_members.data() ),
        static_cast<std::streamsize>(gam._header.npc_party_count * sizeof( GamCharacterData ) ));
    for ( const auto& member : gam._party_members )
        gam._party_cre_files.emplace_back( file_handle, member.cre_offset );

    file_handle.seekg( gam._header.npc_nonparty_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._non_party_members.data() ),
        static_cast<std::streamsize>(gam._header.npc_nonparty_count * sizeof( GamCharacterData ) ));
    for ( const auto& member : gam._non_party_members )
        gam._non_party_cre_files.emplace_back( file_handle, member.cre_offset );

    file_handle.seekg( gam._header.global_vars_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._variables.data() ),
        static_cast<std::streamsize>(gam._header.global_vars_count * sizeof( GamGlobalVariable ) ));

    file_handle.seekg( gam._header.journal_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._journal_entries.data() ),
        static_cast<std::streamsize>(gam._header.journal_count * sizeof( GamJournalEntry ) ));

    file_handle.seekg( gam._header.stored_locs_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._stored_locations.data() ),
        static_cast<std::streamsize>(gam._header.stored_locs_count * sizeof( GamLocationInfo ) ));

    file_handle.seekg( gam._header.pocket_locs_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._pocket_plane_info.data() ),
        static_cast<std::streamsize>(gam._header.pocket_locs_count * sizeof( GamLocationInfo ) ));

    file_handle.seekg( gam._header.familiar_info_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>(&gam._familiar_info), sizeof( GamFamiliarInfo ) );

    file_handle.seekg( gam._header.familiar_extra_offset, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( gam._familiar_extras.data() ),
        static_cast<std::streamsize>(gam._familiar_extras.size() * sizeof( Resref ) ));

    return gam;
}

GamFile::GamFile( const std::string_view path ) noexcept : IEFile( path ) {}

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kGamFileSig;
    const bool valid_version   = _header.version.to_string() == kGamFileVersion_2_0 ||
                                 _header.version.to_string() == kGamFileVersion_2_1;
    
    good = valid_signature && valid_version;
}
