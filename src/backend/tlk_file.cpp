#include "ie_files.h"
#include "tlk_file.h"

#include <algorithm>

#include "utils/io.h"

#include <expected>
#include <format>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

using std::vector;
using std::string_view;
using std::ifstream;

namespace rng = std::ranges;

static constexpr string_view kTlkFileSig( "TLK " );
static constexpr string_view kTlkFileVersion( "V1  " );

TlkLookup TlkFile::at_index( const strref index ) const noexcept
{
    if ( index >= length() )
        return std::unexpected( IEError( IEErrorType::OutOfBounds,
                                         std::format( "TLK: Index {} is out of bounds [0-{}].", index, length() ) ) );
    return _cached_strings[index];
}

TlkLookup TlkFile::operator[]( const strref index ) const noexcept
{
    return at_index( index );
}

u32 TlkFile::length() const noexcept
{
    return _header.entry_count;
}

PossibleTlkFile TlkFile::open( string_view path )
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

    std::vector<TlkFileEntry> _entries;
    _entries.resize( tlk.length() );
    writer.into( _entries, sizeof( TlkFileHeader ) );

    file_handle.seekg( header.offset_to_str_data, std::ios::beg );
    tlk._string_data = std::vector( std::istreambuf_iterator( file_handle ), std::istreambuf_iterator<char>() );
    tlk._cached_strings.reserve( tlk.length() );

    rng::for_each( _entries, [&tlk]( const TlkFileEntry& entry ) {
        const std::string_view st( tlk._string_data.data() + entry.offset_to_string, entry.string_length );
        tlk._cached_strings.push_back( st );
    } );

    return std::move( tlk );
}

const std::string_view* TlkFile::begin() const
{
    return &_cached_strings.front();
}

const std::string_view* TlkFile::end() const
{
    return &_cached_strings.back();
}

TlkFile::TlkFile( const string_view path ) noexcept : IEFile( path ) { }

void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kTlkFileSig;
    const bool valid_version   = _header.version.to_string() == kTlkFileVersion;

    good = valid_signature && valid_version;
}
