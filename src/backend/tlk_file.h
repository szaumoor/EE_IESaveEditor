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

using std::vector;
using std::string;
using std::string_view;

using TlkLookup = std::expected<std::string_view, IEError>;
using PossibleTlkFile = std::expected<TlkFile, IEError>;

class TlkFile final : public IEFile
{
public:
    [[nodiscard]]
    TlkLookup at_index( strref index ) const noexcept;

    [[nodiscard]]
    TlkLookup operator[]( strref index ) const noexcept;

    [[nodiscard]]
    u32 length() const noexcept { return static_cast<u32>(_cached_strings.size()); }

    [[nodiscard]]
    static PossibleTlkFile open( string_view path ) noexcept;

    [[nodiscard]]
    const std::string* begin() const;
    [[nodiscard]]
    const std::string* end() const;

private:
    explicit TlkFile( string_view path ) noexcept;
    TlkFileHeader _header{};
    vector<string> _cached_strings;
    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
