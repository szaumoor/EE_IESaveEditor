#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "aliases.h"
#include "binary_layouts.h"
#include "ie_files.h"

#include <expected>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using std::expected;
using std::string_view;
using std::unexpected;
using std::vector;

using namespace rp::files;

enum class TlkErrorType
{
    InvalidIndex,
    NonValidFile
};

struct TlkError
{
    const TlkErrorType type;
    const std::string message;

    explicit TlkError(const TlkErrorType error_type, std::string msg)
        : type(error_type), message(std::move(msg)) {}
};

class TlkFile final : public IEFile
{
public:
    explicit TlkFile(const char* path) noexcept;
    TlkFile() = delete;

    [[nodiscard]]
    expected<string_view, TlkError> at_index( u32 index ) const noexcept;
    [[nodiscard]]
    u32 string_count() const noexcept { return static_cast<u32>(cached_strings.size()); }

private:
    TlkFileHeader header;
    vector<TlkFileEntry> entries;
    vector<std::string> cached_strings;
    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
