#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "aliases.h"
#include "helper_structs.h"
#include "ie_files.h"

#include <vector>

using rp::files::IEFile;
using std::vector;

namespace {
    #pragma pack(push, 1)
    struct KeyFileHeader
    {
        CharArray<4> signature; // "KEY "
        CharArray<4> version;   // "V1  "
        u32 biff_count;
        u32 resource_count;
        u32 offset_to_biff_entries;
        u32 offset_to_resource_entries;
    };

    struct BiffEntries
    {
        u32 length_biff_file;
        u32 offset_to_biff_filename;
        u16 length_biff_filename_with_null;
        u16 location_file_bitfield;
    };

    struct ResourceEntries
    {
        Resref resource_name;
        u32 resource_type;
        u32 resource_locator;
    };

    #pragma pack(pop)
}

class KeyFile : public IEFile
{
private:
    KeyFileHeader header;
    vector<BiffEntries> biff_entries;
    vector<ResourceEntries> resource_entries;
    void check_for_malformation() noexcept override;
public:
    explicit KeyFile( const char* path ) noexcept;

    [[nodiscard]]
    const u32 get_biff_count() const noexcept { return header.biff_count; }
    [[nodiscard]]
    const u32 get_resource_count() const noexcept { return header.resource_count; }
};

#endif // KEY_FILE_H