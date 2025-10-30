#include "../biff_files.h"
#include "ie_files.h"


BiffFile::BiffFile( const char* path ) noexcept
    : IEFile( path ), header( {} )
{

}

void BiffFile::check_for_malformation() noexcept
{

}