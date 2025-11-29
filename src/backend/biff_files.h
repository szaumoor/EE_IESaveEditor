#ifndef BIFF_FILES_H
#define BIFF_FILES_H

// #include "aliases.h"
#include "binary_layouts.h"
#include "ie_files.h"

#include <string_view>
#include <vector>

using std::vector;

class BiffFile final : IEFile
{
public:
    explicit BiffFile( std::string_view path ) noexcept;
    BiffFile() = delete;

   // [[nodiscard]] u32 file_count() const noexcept { return _header.count_of_file_entries; }
   // [[nodiscard]] u32 tile_count() const noexcept { return _header.count_of_tile_entries; }

private:
    BiffHeader _header;
    vector<FileEntry> _file_entries;
    vector<TileEntry> _tile_entries;
    void check_for_malformation() noexcept override;
};

#endif // BIFF_FILES_H
