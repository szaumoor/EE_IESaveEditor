#include "ie_files.h"
#include "tlk_file.h"

#include <expected>
#include <format>
#include <fstream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

static constexpr std::string_view kTlkFileSig ("TLK ");
static constexpr std::string_view kTlkFileVersion ("V1  ");

PossibleTlkFile TlkFile::open(std::string_view path) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );
    if ( !file_handle )
        return std::unexpected(IEError(IEErrorType::Unreadable, "Could not read the TLK file"));

    TlkFile tlk(path);
    file_handle.read( reinterpret_cast<char*>(&tlk._header), sizeof( TlkFileHeader ) );
    tlk.check_for_malformation();

    if (!tlk)
        return std::unexpected(IEError(IEErrorType::Malformed, "TLK file has wrong signature or is corrupted"));

    std::vector<TlkFileEntry> entries;
    entries.resize( tlk._header.entry_count );

    file_handle.seekg( sizeof(TlkFileHeader), std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( entries.data() ), static_cast<std::streamsize>(tlk._header.entry_count * sizeof( TlkFileEntry ) ));

    file_handle.seekg( tlk._header.offset_to_str_data, std::ios::beg );
    const auto string_data = std::vector(std::istreambuf_iterator( file_handle ),std::istreambuf_iterator<char>());

    for ( const auto& entry: entries )
        tlk._cached_strings.emplace_back( &string_data[entry.offset_to_string], entry.string_length );

    return tlk;
}

TlkFile::TlkFile( const std::string_view path ) noexcept : IEFile(path) {}

TlkLookup TlkFile::at_index( const strref index ) const noexcept
{
    if ( index >= _cached_strings.size() )
        return std::unexpected( IEError( IEErrorType::OutOfBounds,
            std::format("TLK: Index {} is out of bounds! There are {} cached strings.", index, _cached_strings.size() )));

    return _cached_strings[index];
}

TlkLookup TlkFile::operator[](const strref index) const noexcept
{
    return at_index( index );
}


void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kTlkFileSig;
    const bool valid_version   = _header.version.to_string()   == kTlkFileVersion;
    good = valid_signature && valid_version;
}
