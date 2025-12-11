#include "biff_file.h"

#include <fstream>
#include <ios>

#include "ie_files.h"
#include "utils/io.h"

static constexpr std::string_view kBiffSignature( "BIFF" );
static constexpr std::string_view kBiffFileVersion( "V1  " );

PossibleBiffFile BiffFile::open( const std::string_view path ) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );

    if ( !file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    BiffFile biff( path );
    auto& header = biff._header;
    StructWriter writer( file_handle );
    writer.into( header );
    biff.check_for_malformation();

    if ( !biff )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    if ( header.count_of_file_entries > 0 )
    {
        biff._file_entries.resize( header.count_of_file_entries );
        writer.into( biff._file_entries, header.offset_to_file_entries );
    }

    if ( header.count_of_tile_entries > 0 )
    {
        biff._tile_entries.resize( header.count_of_tile_entries );
        writer.into( biff._tile_entries,
                     header.offset_to_file_entries + sizeof( FileEntry ) * header.count_of_file_entries );
    }

    return std::move( biff );
}

BiffFile::BiffFile( const std::string_view path ) noexcept
    : IEFile( path ) { }

void BiffFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kBiffSignature;
    const bool valid_version   = _header.version.to_string() == kBiffFileVersion;

    good = valid_signature && valid_version;
}
