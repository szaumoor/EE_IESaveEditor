#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "aliases.h"
#include "binary_layouts.h"
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

class TlkFile final : public IEFile
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
    expected<string_view, TlkError> at_index( u32 index ) const noexcept;
    [[nodiscard]]
    u32 string_count() const noexcept { return static_cast<u32>(cached_strings.size()); }
};

#endif // TLK_FILE_H
