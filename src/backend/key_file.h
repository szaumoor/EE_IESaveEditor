#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "ie_files.h"
#include "binary_layouts/key_biff.h"

#include <string_view>
#include <vector>

class KeyFile final : public IEFile
{
public:
    explicit KeyFile( std::string_view path ) noexcept;
    KeyFile() = delete;

    // [[nodiscard]] u32 biff_count() const noexcept { return _header.biff_count; }
    // [[nodiscard]] u32 resource_count() const noexcept { return _header.resource_count; }

private:
    KeyFileHeader _header;
    std::vector<BiffEntry> _biff_entries;
    std::vector<ResourceEntry> _resource_entries;
    void check_for_malformation() noexcept override;
};

#endif // KEY_FILE_H