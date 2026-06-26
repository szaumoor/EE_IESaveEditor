#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "ie_files.h"
#include "binary_layouts/tlk.h"
#include "utils/aliases.h"

#include <string_view>
#include <vector>

#include "ie_string.h"

class TlkFile final
{
public:
    TlkFile( const TlkFile& other );
    TlkFile( TlkFile&& other ) noexcept;

    static Possible<TlkFile> open( std::string_view path );

    Possible<IEStringView> at( strref index ) const noexcept; // NOLINT(*-use-nodiscard)
    Possible<IEStringView> operator[]( strref index ) const noexcept;
    explicit operator bool() const noexcept { return m_good; }

    [[nodiscard]] u32 length() const noexcept;
    [[nodiscard]] const std::string_view* begin() const;
    [[nodiscard]] const std::string_view* end() const;
    [[nodiscard]] bool good() const noexcept { return m_good; }
    [[nodiscard]] std::string_view path() const noexcept { return m_path; }
    [[nodiscard]] std::vector<IEStringView> find( std::string_view text,
                            bool case_sensitive = true ) const noexcept;
    void check_for_malformation() noexcept;

private:
    explicit TlkFile(std::string_view path) : m_path{ path } {}
    TlkFileHeader m_header{};
    std::vector<char> m_string_data;
    std::vector<std::string_view> m_cached_strings;
    std::string m_path;
    bool m_good = false;

    void rebuild_cached_strings( const TlkFile& other );
    [[nodiscard]] bool string_data_in_range(const TlkFileEntry& entry) const noexcept;
    void if_in_range( const TlkFileEntry& entry);
};

static_assert(IE_Openable<TlkFile>);

#endif // TLK_FILE_H
