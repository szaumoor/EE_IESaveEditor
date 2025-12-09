#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "binary_layouts/tlk.h"
#include "ie_files.h"
#include "utils/aliases.h"
#include "utils/errors.h"

#include <expected>
#include <string>
#include <string_view>
#include <vector>

class TlkFile;
using TlkLookup       = std::expected<std::string_view, IEError>;
using PossibleTlkFile = std::expected<TlkFile, IEError>;

class TlkFile final : public IEFile
{
public:
    [[nodiscard]]
    TlkLookup at_index( strref index ) const noexcept;

    [[nodiscard]]
    TlkLookup operator[]( strref index ) const noexcept;

    [[nodiscard]]
    u32 length() const noexcept;

    [[nodiscard]]
    static PossibleTlkFile open( std::string_view path ) noexcept;

private:
    explicit TlkFile( std::string_view path ) noexcept;

    TlkFileHeader _header{};
    std::vector<TlkFileEntry> _entries;
    std::vector<char> _string_data;

    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
