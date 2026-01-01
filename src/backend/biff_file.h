#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "ie_files.h"
#include "binary_layouts/key_biff.h"
#include "utils/errors.h"

#include <string_view>
#include <vector>

#include "binary_layouts/spl.h"

class BiffFile final : IEFile
{
public:
    static Possible<BiffFile> open( std::string_view path );

private:
    using IEFile::IEFile;
    void check_for_malformation() noexcept override;

public:
    BiffHeader m_header{};
    std::vector<FileEntry> m_file_entries;
    std::vector<TileEntry> m_tile_entries;
    std::vector<SplHeader> m_spells;
};

#endif // BIFF_FILES_H
