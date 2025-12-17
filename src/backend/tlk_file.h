#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "ie_files.h"
#include "binary_layouts/tlk.h"
#include "utils/aliases.h"
#include "utils/errors.h"

#include <expected>
#include <string_view>
#include <vector>

using TlkLookup = Possible<std::string_view>;

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
    static Possible<TlkFile> open( std::string_view path );

    [[nodiscard]]
    const std::string_view* begin() const;
    [[nodiscard]]
    const std::string_view* end() const;

private:
    explicit TlkFile( std::string_view path ) noexcept;

    TlkFileHeader m_header{};
    std::vector<char> m_string_data;
    std::vector<std::string_view> m_cached_strings;

    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
