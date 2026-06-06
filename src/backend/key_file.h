#ifndef KEY_FILE_H
#define KEY_FILE_H

#include <string_view>
#include <vector>

#include "ie_files.h"
#include "binary_layouts/key_biff.h"
#include "utils/errors.h"

class KeyFile final : public IEFile
{
public:
    static Possible<KeyFile> open( std::string_view path );

protected:
    void check_for_malformation() noexcept override;
private:
    using IEFile::IEFile;
    KeyFileHeader m_header{};
    std::vector<BiffEntry> m_biff_entries;
    std::vector<char> m_location_data;
    std::vector<std::string_view> m_resource_names;
    std::vector<ResourceEntry> m_resource_entries;
};

#endif // KEY_FILE_H
