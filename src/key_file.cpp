#include <fstream>

#include "ie_files.h"
#include "key_file.h"

using namespace rp::files;

constexpr const char* KEY_FILE_SIGNATURE = "KEY ";
constexpr const char* KEY_FILE_VERSION = "V1  ";

KeyFile::KeyFile( const char* path ) noexcept
    : IEFile( path ), header( {} )
{

    std::ifstream gam( path, std::ios::binary );
    if ( gam )
    {
        state = IEFileState::Readable;
        gam.read( reinterpret_cast<char*>(&header), sizeof( KeyFileHeader ) );
        check_for_malformation();

        if ( state == IEFileState::ReadableAndValid )
        {

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

