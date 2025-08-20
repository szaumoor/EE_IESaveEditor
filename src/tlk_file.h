#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "aliases.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <string_view>
#include <string>
#include <vector>
#include <expected>

using std::vector;
using std::string_view;
using std::string;
using std::expected;
using std::unexpected;

using namespace rp::files;

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

enum class TlkErrorType
{
    InvalidIndex,
    NonValidFile
};

struct TlkError
{
    TlkErrorType type;
    string message;
    explicit TlkError(TlkErrorType error_type, const string& msg)
        : type(error_type), message(msg) {}
};

class TlkFile : public IEFile
{
private:
    TlkFileHeader header;
    vector<TlkFileEntry> entries;
    vector<string> cached_strings;
    void check_for_malformation() noexcept override;
public:
    explicit TlkFile(const char* path) noexcept;
    TlkFile() = delete;

    [[nodiscard]]
    const expected<string_view, TlkError> at_index( u32 index ) const noexcept;
    [[nodiscard]]
    const u32 string_count() const noexcept { return static_cast<u32>(cached_strings.size()); }
};

#endif // TLK_FILE_H
