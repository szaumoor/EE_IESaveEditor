#include <fstream>

#include "ie_files.h"
#include "key_file.h"

using namespace rp::files;

constexpr const char* KEY_FILE_SIGNATURE = "KEY ";
constexpr const char* KEY_FILE_VERSION = "V1  ";

KeyFile::KeyFile( const char* path ) noexcept
    : IEFile( path ), header( {} )
{
    if (std::ifstream key( path, std::ios::binary ); key )
    {
        state = IEFileState::Readable;
        key.read( reinterpret_cast<char*>(&header), sizeof( KeyFileHeader ) );
        KeyFile::check_for_malformation();

        if ( state == IEFileState::ReadableAndValid )
        {
            biff_entries.resize( header.biff_count );
            resource_entries.resize( header.resource_count );

            key.seekg( header.offset_to_biff_entries, std::ios::beg );
            key.read( reinterpret_cast<char*>( biff_entries.data() ),
                header.biff_count * sizeof( BiffEntry ) );
            key.seekg( header.offset_to_resource_entries, std::ios::beg );
            key.read( reinterpret_cast<char*>( resource_entries.data() ),
                header.resource_count * sizeof( ResourceEntry ) );
        }
    }
}

void KeyFile::check_for_malformation() noexcept
{
    const bool valid_signature = header.signature.to_string() == KEY_FILE_SIGNATURE;
    const bool valid_version = header.version.to_string() == KEY_FILE_VERSION;
    state = (valid_signature && valid_version)
        ? IEFileState::ReadableAndValid
        : IEFileState::ReadableButMalformed;
}

