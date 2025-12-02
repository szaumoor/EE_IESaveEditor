#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "utils/aliases.h"
#include "binary_layouts/tlk.h"
#include "ie_files.h"

#include <expected>
#include <string>
#include <string_view>
#include <vector>

struct TlkError;

using tlk_lookup = std::expected<std::string_view, TlkError>;

enum class TlkErrorType { InvalidIndex, InvalidFile };

struct TlkError
{
    const TlkErrorType type;
    const std::string message;

    explicit TlkError(const TlkErrorType error_type, const std::string_view msg)
        : type(error_type), message(msg)
    {
    }
};

class TlkFile final : public IEFile
{
public:
    explicit TlkFile(std::string_view path) noexcept;
    TlkFile() = delete;

    [[nodiscard]]
    tlk_lookup at_index( strref index ) const noexcept;
    [[nodiscard]]
    tlk_lookup operator[](strref index) const noexcept;

    [[nodiscard]]
    u32 length() const noexcept { return static_cast<u32>(_cached_strings.size()); }

private:
    TlkFileHeader _header;
    std::vector<std::string> _cached_strings;
    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
