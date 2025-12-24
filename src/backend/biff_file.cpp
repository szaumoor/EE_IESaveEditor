#include "biff_file.h"

#include <fstream>
#include <ios>

#include "ie_files.h"
#include "utils/io.h"

using std::ifstream;

static constexpr std::string_view kBiffSignature( "BIFF" );
static constexpr std::string_view kBiffFileVersion( "V1  " );

Possible<BiffFile> BiffFile::open( const std::string_view path )
{
    ifstream file_handle( path.data(), std::ios::binary );

    if ( not file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    BiffFile biff( path );
    auto& header = biff.m_header;
    StructWriter writer( file_handle );
    writer.into( header );
    biff.check_for_malformation();

    if ( not biff )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    if ( header.count_of_file_entries > 0 )
    {
        biff.m_file_entries.resize( header.count_of_file_entries );
        writer.into( biff.m_file_entries, header.offset_to_file_entries );
    }

    if ( header.count_of_tile_entries > 0 )
    {
        biff.m_tile_entries.resize( header.count_of_tile_entries );
        writer.into( biff.m_tile_entries,
                     header.offset_to_file_entries + sizeof( FileEntry ) * header.count_of_file_entries );
    }

    return std::move( biff );
}

BiffFile::BiffFile( const std::string_view path ) noexcept
    : IEFile( path ) { }

void BiffFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kBiffSignature;
    const bool valid_version   = m_header.version.to_string() == kBiffFileVersion;

    m_good = valid_signature && valid_version;
}
