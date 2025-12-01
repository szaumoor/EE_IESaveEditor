#include "gam_file.h"
#include "utils/helper_structs.h"
#include "ie_files.h"

#include <fstream>
#include <iostream>


static constexpr std::string_view GAM_FILE_SIGNATURE("GAME");
static constexpr std::string_view GAM_FILE_VERSION_2_0("V2.0");
static constexpr std::string GAM_FILE_VERSION_2_1 ("V2.1");

GamFile::GamFile( const std::string_view path ) noexcept
    : IEFile( path ), _header( {} ), _familiar_info( {} )
{
    if (std::ifstream gam( path.data(), std::ios::binary ); !gam )
        state = IEFileState::Unreadable;
    else
    {
        state = IEFileState::Readable;
        gam.read( reinterpret_cast<char*>(&_header), sizeof( GamHeader ) );
        GamFile::check_for_malformation();

        if ( state == IEFileState::Valid )
        {
            _party_members.resize( _header.npc_party_count );
            _non_party_members.resize( _header.npc_nonparty_count );
            _variables.resize( _header.global_vars_count );
            _journal_entries.resize( _header.journal_count );
            _stored_locations.resize( _header.stored_locs_count );
            _pocket_plane_info.resize( _header.pocket_locs_count );
            _familiar_extras.resize( 81 );

            gam.seekg( _header.npc_party_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _party_members.data() ),
                static_cast<std::streamsize>(_header.npc_party_count * sizeof( GamCharacterData ) ));
            for ( const auto& member : _party_members )
                _party_cre_files.emplace_back( gam, member.cre_offset );

            gam.seekg( _header.npc_nonparty_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _non_party_members.data() ),
                static_cast<std::streamsize>(_header.npc_nonparty_count * sizeof( GamCharacterData ) ));
            for ( const auto& member : _non_party_members )
                _non_party_cre_files.emplace_back( gam, member.cre_offset );

            gam.seekg( _header.global_vars_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _variables.data() ),
                static_cast<std::streamsize>(_header.global_vars_count * sizeof( GamGlobalVariable ) ));

            gam.seekg( _header.journal_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _journal_entries.data() ),
                static_cast<std::streamsize>(_header.journal_count * sizeof( GamJournalEntry ) ));

            gam.seekg( _header.stored_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _stored_locations.data() ),
                static_cast<std::streamsize>(_header.stored_locs_count * sizeof( GamLocationInfo ) ));

            gam.seekg( _header.pocket_locs_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _pocket_plane_info.data() ),
                static_cast<std::streamsize>(_header.pocket_locs_count * sizeof( GamLocationInfo ) ));

            gam.seekg( _header.familiar_info_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>(&_familiar_info), sizeof( GamFamiliarInfo ) );

            gam.seekg( _header.familiar_extra_offset, std::ios::beg );
            gam.read( reinterpret_cast<char*>( _familiar_extras.data() ),
                static_cast<std::streamsize>(_familiar_extras.size() * sizeof( Resref ) ));
        }
    }
}

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == GAM_FILE_SIGNATURE;
    const bool valid_version   = _header.version.to_string() == GAM_FILE_VERSION_2_0 ||
                                 _header.version.to_string() == GAM_FILE_VERSION_2_1;

    state = valid_signature && valid_version ? IEFileState::Valid : IEFileState::Malformed;
}
