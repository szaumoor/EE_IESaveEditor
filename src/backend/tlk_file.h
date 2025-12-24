#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "ie_files.h"
#include "binary_layouts/tlk.h"
#include "utils/aliases.h"
#include "utils/errors.h"

#include <expected>
#include <string_view>
#include <vector>


class TlkFile final : public IEFile
{
public:
    Possible<std::string_view> at( strref index ) const noexcept; // NOLINT(*-use-nodiscard)
    Possible<std::string_view> operator[]( strref index ) const noexcept;

    static Possible<TlkFile> open( std::string_view path );

    [[nodiscard]] u32 length() const noexcept;
    [[nodiscard]] const std::string_view* begin() const;
    [[nodiscard]] const std::string_view* end() const;

private:
    explicit TlkFile( std::string_view path ) noexcept;

    TlkFileHeader m_header{};
    std::vector<char> m_string_data;
    std::vector<std::string_view> m_cached_strings;

    void check_for_malformation() noexcept override;
};

#endif // TLK_FILE_H
