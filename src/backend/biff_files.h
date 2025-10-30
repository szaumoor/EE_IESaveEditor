#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "aliases.h"
#include "../binary_layouts.h"
#include "ie_files.h"

#include <vector>

using std::vector;
using rp::files::IEFile;


class BiffFile final : IEFile
{
public:
    explicit BiffFile( const char* path ) noexcept;

    [[nodiscard]]
    u32 file_count() const noexcept { return header.count_of_file_entries; }
    [[nodiscard]]
    u32 tile_count() const noexcept { return header.count_of_tile_entries; }

private:
    BiffHeader header;
    vector<FileEntry> file_entries;
    vector<TileEntry> tile_entries;
    void check_for_malformation() noexcept override;
};

#endif // BIFF_FILES_H
