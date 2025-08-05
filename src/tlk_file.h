#ifndef TLK_FILE_H
#define TLK_FILE_H

#include <cstdint>
#include <vector>
#include <string>
#include <optional>

using std::optional;

namespace
{
    #pragma pack(push, 1)
    struct TlkFileHeader
    {
        char signature[4];
        char version[4];
        uint16_t language_id;
        int32_t entry_count;
        int32_t offset_to_str_data;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct TlkFileEntry
    {
        uint16_t entry_flags;
        char resref[8];
        uint32_t volume;
        uint32_t pitch;
        uint32_t offset_to_string;
        uint32_t string_length;
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
    optional<std::string> at_index( int32_t index ) const;
    TlkFileState get_state() const noexcept { return state; }
};

#endif // TLK_FILE_H
