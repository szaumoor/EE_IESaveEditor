#ifndef KEY_FILE_H
#define KEY_FILE_H

#include <expected>
#include <string_view>
#include <vector>

#include "ie_files.h"
#include "binary_layouts/key_biff.h"
#include "utils/errors.h"

class KeyFile final : public IEFile
{
public:
    [[nodiscard]]
    static Possible<KeyFile> open( std::string_view path ) noexcept;

private:
    explicit KeyFile( std::string_view path ) noexcept;

    KeyFileHeader m_header{};
    std::vector<BiffEntry> m_biff_entries;
    std::vector<ResourceEntry> m_resource_entries;

    void check_for_malformation() noexcept override;
};

#endif // KEY_FILE_H
