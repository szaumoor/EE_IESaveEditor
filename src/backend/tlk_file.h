#ifndef TLK_FILE_H
#define TLK_FILE_H

// #include "aliases.h"
#include "binary_layouts.h"
#include "ie_files.h"

#include <expected>
#include <string>
#include <string_view>
#include <vector>

using std::expected;
using std::string_view;
using std::unexpected;
using std::vector;

enum class TlkErrorType
{
    InvalidIndex,
    InvalidFile
};

struct TlkError
{
    const TlkErrorType type;
    const std::string_view message;

    explicit TlkError(const TlkErrorType error_type, const std::string_view msg)
        : type(error_type), message(msg) {}
};

class TlkFile final : public IEFile
{
public:
    explicit TlkFile(string_view path) noexcept;
    TlkFile() = delete;

    [[nodiscard]] expected<string_view, TlkError> at_index( strref index ) const noexcept;
    [[nodiscard]] u32 length() const noexcept { return static_cast<u32>(_cached_strings.size()); }

private:
    TlkFileHeader _header;
    vector<TlkFileEntry> _entries;
    vector<std::string> _cached_strings;
    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
