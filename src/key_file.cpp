#include "key_file.h"
#include <fstream>
#include "ie_files.h"

using namespace rp::files;

constexpr const char* KEY_FILE_SIGNATURE = "GAME";
constexpr const char* KEY_FILE_VERSION = "V2.0";

KeyFile::KeyFile( const char* path )
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

