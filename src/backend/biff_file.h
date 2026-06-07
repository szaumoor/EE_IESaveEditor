#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "ie_files.h"
#include "binary_layouts/key_biff.h"
#include "binary_layouts/spl.h"
#include "utils/errors.h"

#include <string_view>
#include <vector>

class BiffFile final : IEFile
{
public:
    static Possible<BiffFile> open( std::string_view path );

protected:
    void check_for_malformation() noexcept override;

private:
    using IEFile::IEFile;

public:
    BiffHeader m_header{};
    std::vector<FileEntry> m_file_entries;
    std::vector<TileEntry> m_tile_entries;

    std::vector<SplHeader> m_spells;
    std::vector<std::string> m_ids_files;
    std::vector<std::string> m_ini_files;
};

#endif // BIFF_FILES_H
