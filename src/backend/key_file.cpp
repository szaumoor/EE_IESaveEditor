#include <fstream>
#include <string_view>

#include "key_file.h"
#include "ie_files.h"
#include "utils/io.h"

using std::string_view;
using std::vector;
using std::ifstream;

static constexpr string_view kKeyFileSig( "KEY " );
static constexpr string_view kKeyFileVersion( "V1  " );

Possible<KeyFile> KeyFile::open( const string_view path )
{
    ifstream file_handle( path.data(), std::ios::binary );

    if ( not file_handle )
        return std::unexpected( IEError( IEErrorType::Unreadable ) );

    KeyFile key( path );
    StructWriter writer( file_handle );
    writer.into( key.m_header );
    key.check_for_malformation();

    if ( not key )
        return std::unexpected( IEError( IEErrorType::Malformed ) );

    key.m_biff_entries.resize( key.m_header.biff_count );
    key.m_resource_entries.resize( key.m_header.resource_count );

    writer.into( key.m_biff_entries, key.m_header.offset_to_biff_entries );
    writer.into( key.m_resource_entries, key.m_header.offset_to_resource_entries );

    return key;
}

KeyFile::KeyFile( const string_view path ) noexcept : IEFile( path ) { }

void KeyFile::check_for_malformation() noexcept
{
    const bool valid_signature = m_header.signature.to_string() == kKeyFileSig;
    const bool valid_version   = m_header.version.to_string() == kKeyFileVersion;

    m_good = valid_signature && valid_version;
}
