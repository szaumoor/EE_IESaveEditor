#ifndef KEY_FILE_H
#define KEY_FILE_H

#include <string_view>
#include <vector>

#include "ie_files.h"
#include "binary_layouts/key_biff.h"
#include "utils/errors.h"

class KeyFile final
{
public:
    static Possible<KeyFile> open( std::string_view path );
    void check_for_malformation() noexcept;
    explicit operator bool() const noexcept { return m_good; }

    [[nodiscard]]
    bool good() const noexcept { return m_good; }

    [[nodiscard]]
    std::string_view path() const noexcept { return m_path; }

private:
    explicit KeyFile( const std::string_view path) : m_path(path) {}
    KeyFileHeader m_header{};
    std::vector<BiffEntry> m_biff_entries;
    std::vector<char> m_location_data;
    std::vector<std::string_view> m_resource_names;
    std::vector<ResourceEntry> m_resource_entries;

    std::string m_path;
    bool m_good = false;
};
static_assert(IE_Openable<KeyFile>);


#endif // KEY_FILE_H
