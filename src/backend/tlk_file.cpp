#include "aliases.h"
#include "ie_files.h"
#include "tlk_file.h"

#include <expected>
#include <format>
#include <fstream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

constexpr auto TLK_FILE_SIGNATURE = "TLK ";
constexpr auto TLK_FILE_VERSION   = "V1  ";


TlkFile::TlkFile( const std::string_view path ) noexcept
    : IEFile(path), _header({})
{
    if (std::ifstream tlk( path.data(), std::ios::binary ); !tlk)
        state = IEFileState::Unreadable;
    else {
        state = IEFileState::Readable;
        tlk.read( reinterpret_cast<char*>(&_header), sizeof( TlkFileHeader ) );
        TlkFile::check_for_malformation();

        if ( good() )
        {
            _entries.resize( _header.entry_count );

            tlk.seekg( sizeof(TlkFileHeader), std::ios::beg );
            tlk.read( reinterpret_cast<char*>( _entries.data() ), static_cast<std::streamsize>(_header.entry_count * sizeof( TlkFileEntry ) ));

            tlk.seekg( _header.offset_to_str_data, std::ios::beg );
            const auto string_data = std::vector(std::istreambuf_iterator( tlk ),std::istreambuf_iterator<char>());

            for ( const auto& entry: _entries )
                _cached_strings.emplace_back( &string_data[entry.offset_to_string], entry.string_length );
        }
    }
}

expected<string_view, TlkError> TlkFile::at_index( const strref index ) const noexcept
{
    if ( state != IEFileState::Valid )
        return std::unexpected( TlkError( TlkErrorType::InvalidFile,
            "The TLK file is not valid or readable." ) );

    if ( index >= _cached_strings.size() )
        return std::unexpected( TlkError( TlkErrorType::InvalidIndex,
            std::format("The requested index {} is out of bounds", index)));

    return _cached_strings[index];
}

void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = _header.signature.to_string() == TLK_FILE_SIGNATURE;
    const bool valid_version   = _header.version.to_string()   == TLK_FILE_VERSION;
    state = valid_signature && valid_version ? IEFileState::Valid : IEFileState::Malformed;
}
