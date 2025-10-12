#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "aliases.h"
#include "binary_layouts.h"
#include "ie_files.h"

#include <vector>

using rp::files::IEFile;
using std::vector;

class KeyFile final : public IEFile
{
    KeyFileHeader header;
    vector<BiffEntry> biff_entries;
    vector<ResourceEntry> resource_entries;
    void check_for_malformation() noexcept override;
public:
    explicit KeyFile( const char* path ) noexcept;

    [[nodiscard]]
    u32 biff_count() const noexcept { return header.biff_count; }
    [[nodiscard]]
    u32 resource_count() const noexcept { return header.resource_count; }
};

#endif // KEY_FILE_H