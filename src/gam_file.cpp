#include "gam_file.h"
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

        }
    }
}

void GamFile::check_for_malformation() noexcept
{
    const bool valid_signature = header.signature.to_string() == GAM_FILE_SIGNATURE;
    const bool valid_version   = header.version.to_string() == GAM_FILE_VERSION;
    state = (valid_signature && valid_version)
        ? IEFileState::ReadableAndValid
        : IEFileState::ReadableButMalformed;
}
