#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "aliases.h"
#include <vector>
#include <string>
#include <optional>
#include "helper_structs.h"

using std::optional;

namespace
{
    #pragma pack(push, 1)
    struct TlkFileHeader
    {
        CharArray<4> signature; // "TLK "
        CharArray<4> version;   // "V1  "
        u16 language_id;
        u32 entry_count;
        u32 offset_to_str_data;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct TlkFileEntry
    {
        u16 entry_flags;
        CharArray<8> resref;
        u32 volume;
        u32 pitch;
        u32 offset_to_string;
        u32 string_length;
    };
    #pragma pack(pop)
}

enum class TlkFileState
{
    Unreadable,
    Readable,
    ReadableButMalformed,
    ReadableAndValid
};

class TlkFile
{
    TlkFileHeader header;
    std::vector<TlkFileEntry> entries;
    std::vector<std::string> cached_strings;
    TlkFileState state = TlkFileState::Unreadable;
public:
    explicit TlkFile(const char* path) noexcept;
    explicit operator bool() const noexcept { return state == TlkFileState::ReadableAndValid; }
    optional<std::string> at_index( u32 index ) const;
    TlkFileState get_state() const noexcept { return state; }
};

#endif // TLK_FILE_H
