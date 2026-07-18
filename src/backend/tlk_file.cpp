#include "tlk_file.h"
#include "utils/io.h"

#include <algorithm>
#include <expected>
#include <format>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

#include <print>

namespace rng = std::ranges;

static constexpr auto kTlkFileSig( "TLK " );
static constexpr auto kTlkFileVersion( "V1  " );

TlkFile::TlkFile( const TlkFile& other ) :
    m_header( other.m_header ),
    m_string_data( other.m_string_data ),
    m_path( other.m_path )

{
    m_good = other.m_good;
    rebuild_cached_strings( other );
}

TlkFile::TlkFile( TlkFile&& other ) noexcept
    : m_header( other.m_header ),
      m_string_data( std::move( other.m_string_data ) ),
      m_cached_strings( std::move( other.m_cached_strings ) ),
      m_path( std::move(other.m_path) )
{
    m_good = other.m_good;
}

Possible<TlkFile> TlkFile::open( std::string_view path )
{
    std::ifstream file_handle( path.data(), std::ios::binary );
    if ( not file_handle )
        return NotPossible( IEError( IEErrorType::Unreadable ) );

    TlkFile tlk( path );
    auto& header = tlk.m_header;
    const StructWriter writer( file_handle );

    writer.into( header );
    tlk.check_for_malformation();

    if ( not tlk )
        return NotPossible( IEError( IEErrorType::Malformed ) );

    std::vector<TlkFileEntry> entries( tlk.length() );
    writer.into( entries, sizeof( TlkFileHeader ) );

    file_handle.seekg( header.offset_to_str_data, std::ios::beg );
    tlk.m_string_data = std::vector( std::istreambuf_iterator( file_handle ), std::istreambuf_iterator<char>() );
    tlk.m_cached_strings.reserve( tlk.length() );
    for (const auto& entry : entries)
    {
        tlk.m_cached_strings.emplace_back(
            tlk.m_string_data.data()+entry.offset_to_string, entry.string_length );
    }
    return tlk;
}

Possible<IEStringView> TlkFile::at( const strref index ) const noexcept
{
    if ( index >= length() )
        return NotPossible( IEError( IEErrorType::OutOfBounds,
                                         std::format( "Unknown index {}", index )));
    return IEStringView(m_cached_strings[index], index);
}

Possible<IEStringView> TlkFile::operator[]( const strref index ) const noexcept
{
    return at( index );
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

std::vector<IEStringView> TlkFile::find( const std::string_view text,
    const TlkCase cs, const u32 stop_at ) const
{
    if ( text.empty() )
        return {};

    std::vector<IEStringView> entries;
    if (stop_at > 0)
        entries.reserve( std::min<u32>(stop_at, static_cast<u32>(m_cached_strings.size())) ) ;

    if (cs == TlkCase::Sensitive)
    {
        for (u32 i = 0; i < m_cached_strings.size(); ++i)
        {
            if ( const auto& entry = m_cached_strings[i];
                 entry.find(text) != std::string_view::npos)
            {
                entries.push_back( IEStringView(entry, i) );
            }

            if (stop_at > 0 and entries.size() >= stop_at)
                break;
        }
    }
    else if (cs == TlkCase::Insensitive)
    {
        for (u32 i = 0; i < m_cached_strings.size(); ++i)
        {
            const auto& entry = m_cached_strings[i];

            if (entry.size() < text.size())
                continue;

            const auto match = not std::ranges::search(entry, text, []( const u8 a, const u8 b) {
                    return std::tolower(a) == std::tolower(b);
                }).empty();

            if (match)
                entries.push_back( IEStringView(entry, i) );

            if (stop_at > 0 and entries.size() >= stop_at)
                break;
        }
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
