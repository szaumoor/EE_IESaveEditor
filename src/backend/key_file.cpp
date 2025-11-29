#include <fstream>

#include "ie_files.h"
#include "key_file.h"

constexpr auto KEY_FILE_SIGNATURE = "KEY ";
constexpr auto KEY_FILE_VERSION = "V1  ";

KeyFile::KeyFile( const std::string_view path ) noexcept
    : IEFile( path ), _header( {} )
{
    if (std::ifstream key( path.data(), std::ios::binary ); !key )
        state = IEFileState::Unreadable;
    else {
        state = IEFileState::Readable;
        key.read( reinterpret_cast<char*>(&_header), sizeof( KeyFileHeader ) );
        KeyFile::check_for_malformation();

        if ( good() )
        {
            _biff_entries.resize( _header.biff_count );
            _resource_entries.resize( _header.resource_count );

            key.seekg( _header.offset_to_biff_entries, std::ios::beg );
            key.read( reinterpret_cast<char*>( _biff_entries.data() ),
                static_cast<std::streamsize>(_header.biff_count * sizeof( BiffEntry ) ));
            key.seekg( _header.offset_to_resource_entries, std::ios::beg );
            key.read( reinterpret_cast<char*>( _resource_entries.data() ),
                static_cast<std::streamsize>(_header.resource_count * sizeof( ResourceEntry ) ));
        }
    }
}

void KeyFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == KEY_FILE_SIGNATURE;
    const bool valid_version = _header.version.to_string() == KEY_FILE_VERSION;
    state = valid_signature && valid_version ? IEFileState::Valid : IEFileState::Malformed;
}

