#include <fstream>
#include <string_view>

#include "ie_files.h"
#include "key_file.h"

using std::string_view;

static constexpr std::string_view kKeyFileSig("KEY ");
static constexpr std::string_view kKeyFileVersion("V1  ");

PossibleKeyFile KeyFile::open(const std::string_view path) noexcept
{
    std::ifstream file_handle( path.data(), std::ios::binary );

    if (!file_handle)
        return std::unexpected(IEError(IEErrorType::Unreadable, "Could not read the TLK file"));

    KeyFile key(path);
    file_handle.read( reinterpret_cast<char*>(&key._header), sizeof( KeyFileHeader ) );
    key.check_for_malformation();

    if (!key)
        return std::unexpected(IEError(IEErrorType::Malformed, "TLK file has wrong signature or is corrupted"));

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

KeyFile::KeyFile( const std::string_view path ) noexcept : IEFile( path ) {}

void KeyFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == kKeyFileSig;
    const bool valid_version = _header.version.to_string() == kKeyFileVersion;
    good = valid_signature && valid_version;
}

