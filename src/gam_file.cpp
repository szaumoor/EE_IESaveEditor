#include "cre_file.h"
#include "gam_file.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <fstream>

using rp::files::IEFileState;

constexpr const char* GAM_FILE_SIGNATURE = "GAME";
constexpr const char* GAM_FILE_VERSION   = "V2.0";

GamFile::GamFile( const char* path )
    : IEFile( path ), header( {} ), familiar_info( {} )
{
    std::ifstream gam( path, std::ios::binary );
    if ( gam )
    {
        state = IEFileState::Readable;
        gam.read( reinterpret_cast<char*>(&header), sizeof( GamHeader ) );
        check_for_malformation();

        if ( state == IEFileState::ReadableAndValid )
        {
            party_members.resize( header.npc_party_count );
            non_party_members.resize( header.npc_nonparty_count );
            variables.resize( header.global_vars_count );
            journal_entries.resize( header.journal_count );
            stored_locations.resize( header.stored_locs_count );
            pocket_plane_info.resize( header.pocket_locs_count );
            familiar_extras.resize( 81 );

            gam.seekg( header.npc_party_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( party_members.data() ),
                party_members.size() * sizeof( GamCharacterData ) );

            for ( const auto& member : party_members )
                party_cre_files.push_back( CreFile( gam, member.cre_offset ) );

            gam.seekg( header.npc_nonparty_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( non_party_members.data() ),
                non_party_members.size() * sizeof( GamCharacterData ) );

            for ( const auto& member : non_party_members )
                non_party_cre_files.push_back( CreFile( gam, member.cre_offset ) );

            gam.seekg( header.global_vars_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( variables.data() ),
                variables.size() * sizeof( GamGlobalVariables ) );
            gam.seekg( header.journal_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( journal_entries.data() ),
                journal_entries.size() * sizeof( GamJournalEntry ) );
            gam.seekg( header.stored_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( stored_locations.data() ),
                stored_locations.size() * sizeof( GamLocationInfo ) );
            gam.seekg( header.pocket_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( pocket_plane_info.data() ),
                pocket_plane_info.size() * sizeof( GamLocationInfo ) );
            gam.seekg( header.familiar_info_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>(&familiar_info), sizeof( GamFamiliarInfo ) );
            gam.seekg( header.familiar_extra_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( familiar_extras.data() ),
                familiar_extras.size() * sizeof( Resref ) );
        }
    }
}

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = header.signature.to_string() == GAM_FILE_SIGNATURE;
    const bool valid_version   = header.version.to_string()   == GAM_FILE_VERSION;
    state = (valid_signature && valid_version)
        ? IEFileState::ReadableAndValid
        : IEFileState::ReadableButMalformed;
}
