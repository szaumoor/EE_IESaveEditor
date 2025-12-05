#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "binary_layouts/key_biff.h"
#include "ie_files.h"

#include <string_view>
#include <vector>

class BiffFile final : IEFile
{
public:
    explicit BiffFile( std::string_view path ) noexcept;
    BiffFile() = delete;
private:
    BiffHeader _header;
    std::vector<FileEntry> _file_entries;
    std::vector<TileEntry> _tile_entries;
    void check_for_malformation() noexcept override;
};

#endif // BIFF_FILES_H
