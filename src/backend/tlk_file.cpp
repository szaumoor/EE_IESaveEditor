#include "tlk_file.h"
#include "ie_files.h"
#include "utils/io.h"

#include <algorithm>
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

TlkFile::TlkFile( const TlkFile& other ) :
      IEFile( other.m_path ),
      m_header( other.m_header ),
      m_string_data( other.m_string_data )

{
    m_good = other.m_good;
    rebuild_cached_strings( other );
}

TlkFile::TlkFile( TlkFile&& other ) noexcept
    : IEFile( other.m_path ),
      m_header( other.m_header ),
      m_string_data( std::move( other.m_string_data ) ),
      m_cached_strings( std::move( other.m_cached_strings ) )
{
    m_good = other.m_good;
}

Possible<IEStringView> TlkFile::at( const strref index ) const noexcept
{
    if ( index >= length() )
        return std::unexpected( IEError( IEErrorType::OutOfBounds,
                                         std::format( "TLK: Index {} is out of bounds [0-{}].", index, length()-1 ) ) );
    return IEStringView(m_cached_strings[index], index);
}

Possible<IEStringView> TlkFile::operator[]( const strref index ) const noexcept
{
    return at( index );
}

Possible<TlkFile> TlkFile::open( string_view path )
{
    ifstream file_handle( path.data(), std::ios::binary );
    if ( not file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    TlkFile tlk( path );
    auto& header = tlk.m_header;
    const StructWriter writer( file_handle );

    writer.into( header );
    tlk.check_for_malformation();

    if ( not tlk )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    vector<TlkFileEntry> entries( tlk.length() );
    writer.into( entries, sizeof( TlkFileHeader ) );

    file_handle.seekg( header.offset_to_str_data, std::ios::beg );
    tlk.m_string_data = vector( std::istreambuf_iterator( file_handle ), std::istreambuf_iterator<char>() );
    tlk.m_cached_strings.reserve( tlk.length() );
    rng::for_each( entries, [&tlk]( const TlkFileEntry& entry ) {
        tlk.if_in_range( entry );
    } );
    return tlk;
}

u32 TlkFile::length() const noexcept
{
    return m_header.entry_count;
}

const std::string_view* TlkFile::begin() const
{
    return m_cached_strings.data();
}

const std::string_view* TlkFile::end() const
{
    return begin() + m_cached_strings.size();
}

std::vector<IEStringView> TlkFile::find( const std::string_view text, const bool case_sensitive ) const noexcept
{
    if ( text.empty() )
        return {};

    std::vector<IEStringView> entries;

    u32 index = 0;
    for (const auto& entry : m_cached_strings)
    {
        if (case_sensitive)
        {
            if (entry.find(text) != std::string_view::npos)
                entries.push_back( IEStringView(entry, index) );
        }
        else
        {
            const auto match = not std::ranges::search(entry, text, []( const u8 a, const u8 b) {
                return std::tolower(a) == std::tolower(b);
            }).empty();

            if (match)
                entries.push_back( IEStringView(entry, index) );
        }

        ++index;
    }

    return entries;
}

void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kTlkFileSig;
    const bool valid_version   = m_header.version.to_string() == kTlkFileVersion;

    m_good = valid_signature && valid_version;
}

void TlkFile::rebuild_cached_strings( const TlkFile& other )
{
    m_cached_strings.clear();
    m_cached_strings.reserve( other.m_cached_strings.size() );

    if ( other.m_cached_strings.empty() )
        return;

    const char* old_base = other.m_string_data.data();
    const char* new_base = m_string_data.data();

    for ( const auto& view : other.m_cached_strings )
    {
        if ( view.data() == nullptr )
        {
            m_cached_strings.emplace_back();
            continue;
        }

        const auto offset = static_cast<size_t>( view.data() - old_base );
        m_cached_strings.emplace_back( new_base + offset, view.size() );
    }
}

bool TlkFile::string_data_in_range( const TlkFileEntry& entry) const noexcept
{
    const u32 string_bytes = entry.offset_to_string+entry.string_length;
    return string_bytes <= m_string_data.size();
}

void TlkFile::if_in_range( const TlkFileEntry& entry )
{
    if ( string_data_in_range( entry ) ) [[likely]]
        m_cached_strings.emplace_back(
            m_string_data.data()+entry.offset_to_string, entry.string_length );
}
