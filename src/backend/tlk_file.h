#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "ie_files.h"
#include "binary_layouts/tlk.h"
#include "utils/aliases.h"
#include "utils/errors.h"

#include <string_view>
#include <vector>

#include "ie_string.h"

class TlkFile final : public IEFile
{
public:
    TlkFile( const TlkFile& other );
    TlkFile( TlkFile&& other ) noexcept;

    Possible<IEStringView> at( strref index ) const noexcept; // NOLINT(*-use-nodiscard)
    Possible<IEStringView> operator[]( strref index ) const noexcept;

    static Possible<TlkFile> open( std::string_view path );

    [[nodiscard]] u32 length() const noexcept;
    [[nodiscard]] const std::string_view* begin() const;
    [[nodiscard]] const std::string_view* end() const;

    using IEFile::IEFile;

protected:
    void check_for_malformation() noexcept override;

private:
    TlkFileHeader m_header{};
    std::vector<char> m_string_data;
    std::vector<std::string_view> m_cached_strings;
    void rebuild_cached_strings( const TlkFile& other );

};

#endif // TLK_FILE_H
