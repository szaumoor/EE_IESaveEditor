#include "tlk_file.h"
#include <cstdint>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <iterator>
#include "exceptions.h"

TlkFile::TlkFile( const char* path )
    : header( {} )
{
    std::ifstream tlk( path, std::ios::binary );
    if (tlk)
    {
        state = TlkFileState::Readable;
        tlk.read( reinterpret_cast<char*>(&header), sizeof( TlkFileHeader ) );
        bool valid_signature = std::string( header.signature, 4 ) == "TLK ";
        bool valid_version = std::string( header.version, 4 ) == "V1  ";

        if ( valid_signature && valid_version )
            state = TlkFileState::ReadableAndValid;
        else
            state = TlkFileState::ReadableButMalformed;

        if (state == TlkFileState::ReadableAndValid)
        {
            entries.resize( header.entry_count );
            cached_strings.resize( header.entry_count );
            tlk.seekg( sizeof(TlkFileHeader), std::ios::beg);
            tlk.read( reinterpret_cast<char*>(entries.data()),
                entries.size() * sizeof( TlkFileEntry ) );

            tlk.seekg( header.offset_to_str_data, std::ios::beg );
            std::vector<char> string_data;
            string_data = std::vector<char>(
                std::istreambuf_iterator<char>( tlk ),
                std::istreambuf_iterator<char>()
            );

            for ( size_t i = 0; i < entries.size(); ++i )
            {
                const auto& entry = entries[i];
                const uint32_t offset = entry.offset_to_string;
                cached_strings[i] = std::string( &string_data[offset], entry.string_length );
            }
        }
    }

}

optional<std::string> TlkFile::at_index(const int32_t index) const
{
    if (state != TlkFileState::ReadableAndValid)
        throw InvalidStateOperationError( "TlkFile is not readable and valid." );

    const auto length = static_cast<int32_t>(cached_strings.size());
    if (index < 0 || index >= length) {
        return std::nullopt;
    }

    return std::string(cached_strings[index]);
}
