#include "biff_files.h"
#include "ie_files.h"


BiffFile::BiffFile( const std::string_view path ) noexcept
    : IEFile( path ), _header( {} )
{

}

void BiffFile::check_for_malformation() noexcept
{

}