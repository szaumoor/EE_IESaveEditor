#include "biff_file.h"
#include "ie_files.h"


PossibleBiffFile BiffFile::open(const std::string_view path) noexcept
{
    BiffFile biff(path);
    return std::move(biff);
}

BiffFile::BiffFile( const std::string_view path ) noexcept
    : IEFile( path ), _header( {} )
{
}

void BiffFile::check_for_malformation() noexcept
{

}