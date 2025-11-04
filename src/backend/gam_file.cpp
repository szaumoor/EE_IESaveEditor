#include "gam_file.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <fstream>
#include <iostream>

using rp::files::IEFileState;

static constexpr auto GAM_FILE_SIGNATURE   = "GAME";
static constexpr auto GAM_FILE_VERSION_2_0 = "V2.0";
static constexpr auto GAM_FILE_VERSION_2_1 = "V2.1";

GamFile::GamFile( const char* path ) noexcept
    : IEFile( path ), header( {} ), familiar_info( {} )
{
    if (std::ifstream gam( path, std::ios::binary ); gam )
    {
        state = IEFileState::Readable;
        gam.read( reinterpret_cast<char*>(&header), sizeof( GamHeader ) );
        GamFile::check_for_malformation();

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
                header.npc_party_count * sizeof( GamCharacterData ) );
            for ( const auto& member : party_members )
                party_cre_files.emplace_back( gam, member.cre_offset );

            gam.seekg( header.npc_nonparty_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( non_party_members.data() ),
                header.npc_nonparty_count * sizeof( GamCharacterData ) );
            for ( const auto& member : non_party_members )
                non_party_cre_files.emplace_back( gam, member.cre_offset );

            gam.seekg( header.global_vars_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( variables.data() ),
                header.global_vars_count * sizeof( GamGlobalVariable ) );

            gam.seekg( header.journal_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( journal_entries.data() ),
                header.journal_count * sizeof( GamJournalEntry ) );

            gam.seekg( header.stored_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( stored_locations.data() ),
                header.stored_locs_count * sizeof( GamLocationInfo ) );

            gam.seekg( header.pocket_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( pocket_plane_info.data() ),
                header.pocket_locs_count * sizeof( GamLocationInfo ) );

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
    const bool valid_version   = header.version.to_string() == GAM_FILE_VERSION_2_0 ||
                                 header.version.to_string() == GAM_FILE_VERSION_2_1;
    state = (valid_signature && valid_version)
        ? IEFileState::ReadableAndValid
        : IEFileState::ReadableButMalformed;
}
