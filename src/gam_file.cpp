#include "gam_file.h"
#include "ie_files.h"


constexpr const char* GAM_FILE_SIGNATURE = "GAM";
constexpr const char* GAM_FILE_VERSION   = "V2.0";

GamFile::GamFile( const char* path )
    : IEFile( path ), header( {} ), familiar_info( {} )
{

}
