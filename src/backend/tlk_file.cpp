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

TlkFile::TlkFile( const char* path ) noexcept
    : IEFile(path), header({})
{
    if (std::ifstream tlk( path, std::ios::binary ); tlk)
    {
        state = IEFileState::Readable;
        tlk.read( reinterpret_cast<char*>(&header), sizeof( TlkFileHeader ) );
        TlkFile::check_for_malformation();

        if (state == IEFileState::ReadableAndValid)
        {
            entries.resize( header.entry_count );
            cached_strings.resize( header.entry_count );

            tlk.seekg( sizeof(TlkFileHeader), std::ios::beg );
            tlk.read( reinterpret_cast<char*>( entries.data() ),
                header.entry_count * sizeof( TlkFileEntry ) );

            tlk.seekg( header.offset_to_str_data, std::ios::beg );
            std::vector<char> string_data;
            string_data = std::vector<char>(
                std::istreambuf_iterator<char>( tlk ),
                std::istreambuf_iterator<char>()
            );

            for ( size_t i = 0; i < entries.size(); ++i )
            {
                const auto& entry = entries[i];
                const u32 offset = entry.offset_to_string;
                cached_strings[i] = std::string( &string_data[offset], entry.string_length );
            }
        }
    }
}

expected<string_view, TlkError> TlkFile::at_index( const u32 index ) const noexcept
{
    if ( state != IEFileState::ReadableAndValid )
        return std::unexpected( TlkError( TlkErrorType::NonValidFile,
            "The TLK file is not valid or readable." ) );

    if ( index >= cached_strings.size() )
        return std::unexpected( TlkError( TlkErrorType::InvalidIndex,
            std::format("The requested index {} is out of bounds", index)));

    return cached_strings[index];
}

void TlkFile::check_for_malformation() noexcept
{
    const bool valid_signature = header.signature.to_string() == TLK_FILE_SIGNATURE;
    const bool valid_version   = header.version.to_string()   == TLK_FILE_VERSION;
    state = ( valid_signature && valid_version )
            ? IEFileState::ReadableAndValid
            : IEFileState::ReadableButMalformed;
}
