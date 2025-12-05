#include <fstream>
#include <string_view>

#include "ie_files.h"
#include "key_file.h"

static constexpr string_view kKeyFileSig("KEY ");
static constexpr string_view kKeyFileVersion("V1  ");

PossibleKeyFile KeyFile::open(const string_view path) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );

    if (!file_handle)
        return std::unexpected(IEError(IEErrorType::Unreadable));

    KeyFile key(path);
    file_handle.read( reinterpret_cast<char*>(&key._header), sizeof( KeyFileHeader ) );
    key.check_for_malformation();

    if (!key)
        return std::unexpected(IEError(IEErrorType::Malformed));

    key._biff_entries.resize( key._header.biff_count );
    key._resource_entries.resize( key._header.resource_count );

    file_handle.seekg( key._header.offset_to_biff_entries, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( key._biff_entries.data() ),
        static_cast<std::streamsize>(key._header.biff_count * sizeof( BiffEntry ) ));
    file_handle.seekg( key._header.offset_to_resource_entries, std::ios::beg );
    file_handle.read( reinterpret_cast<char*>( key._resource_entries.data() ),
        static_cast<std::streamsize>(key._header.resource_count * sizeof( ResourceEntry ) ));

    return key;
}

KeyFile::KeyFile( const string_view path ) noexcept : IEFile( path ) {}

void KeyFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kKeyFileSig;
    const bool valid_version = _header.version.to_string() == kKeyFileVersion;
    good = valid_signature && valid_version;
}

