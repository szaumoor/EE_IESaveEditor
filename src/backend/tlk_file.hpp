#ifndef TLK_FILE_H
#define TLK_FILE_H

#include "ie_files.hpp"
#include "binary_layouts/tlk.hpp"
#include "utils/aliases.hpp"
#include "utils/ie_string.hpp"

#include <string_view>
#include <vector>


enum struct TlkCase : u8
{
    Sensitive = 0,
    Insensitive = 1
};

class TlkFile final : public IEClass
{
public:
    TlkFile( const TlkFile& other );
    TlkFile( TlkFile&& other ) noexcept;

    static Possible<TlkFile> open( std::string_view path );

    [[nodiscard]]
    Possible<IEStringView> at( strref index ) const noexcept;
    Possible<IEStringView> operator[]( const strref index ) const noexcept
    {
        return at(index);
    }

    [[nodiscard]] bool good() const noexcept { return m_good; }
    explicit operator bool() const noexcept { return m_good; }

    [[nodiscard]] u32 length() const noexcept { return m_header.entry_count; }
    [[nodiscard]] std::string_view path() const noexcept { return m_path; }

    [[nodiscard]] const std::string_view* begin() const;
    [[nodiscard]] const std::string_view* end() const;
    [[nodiscard]] std::vector<IEStringView> find( std::string_view text,
                                                  TlkCase cs = TlkCase::Sensitive, u32 stop_at = 0 ) const;
    void check_for_malformation() noexcept;

private:
    explicit TlkFile( const std::string_view path) : m_path{ path } {}
    TlkFileHeader m_header {};
    std::vector<char> m_string_data;
    std::vector<std::string_view> m_cached_strings;
    std::string m_path;
    bool m_good { false };

    void rebuild_cached_strings( const TlkFile& other );
};

static_assert(IE_Openable<TlkFile>);

#endif // TLK_FILE_H
