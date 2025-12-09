#include "ie_files.h"
#include "tlk_file.h"
#include "utils/io.h"

#include <expected>
#include <format>
#include <fstream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

using std::vector;
using std::string;
using std::string_view;

static constexpr string_view kTlkFileSig( "TLK " );
static constexpr string_view kTlkFileVersion( "V1  " );

TlkLookup TlkFile::at_index( const strref index ) const noexcept
{
    if ( index >= length() )
        return std::unexpected( IEError( IEErrorType::OutOfBounds,
                                         std::format( "TLK: Index {} is out of bounds! There are {} cached strings.",
                                                      index, _entries.size() ) ) );
    const auto& entry = _entries[index];
    return std::string_view ( _string_data.data() + entry.offset_to_string, entry.string_length );;
}

TlkLookup TlkFile::operator[]( const strref index ) const noexcept
{
    return at_index( index );
}

u32 TlkFile::length() const noexcept
{
    return _header.entry_count;
}

PossibleTlkFile TlkFile::open( string_view path ) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );
    if ( !file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    TlkFile tlk( path );
    auto& header = tlk._header;
    const StructWriter writer( file_handle );

    writer.into( header );
    tlk.check_for_malformation();

    if ( !tlk )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    tlk._entries.resize( tlk.length() );
    writer.into( tlk._entries, sizeof( TlkFileHeader ) );

    file_handle.seekg( tlk._header.offset_to_str_data, std::ios::beg );
    tlk._string_data = std::vector( std::istreambuf_iterator( file_handle ), std::istreambuf_iterator<char>() );

    return std::move( tlk );
}

TlkFile::TlkFile( const string_view path ) noexcept : IEFile( path ) { }

void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kTlkFileSig;
    const bool valid_version   = _header.version.to_string() == kTlkFileVersion;

    good = valid_signature && valid_version;
}
