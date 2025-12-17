#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "binary_layouts/key_biff.h"
#include "ie_files.h"
#include "utils/errors.h"

#include <expected>
#include <string_view>
#include <vector>

class BiffFile;
using PossibleBiffFile = std::expected<BiffFile, IEError>;

class BiffFile final : IEFile
{
public:
    [[nodiscard]]
    static PossibleBiffFile open( std::string_view path ) noexcept;

private:
    explicit BiffFile( std::string_view path ) noexcept;

    BiffHeader m_header{};
    std::vector<FileEntry> m_file_entries;
    std::vector<TileEntry> m_tile_entries;

    void check_for_malformation() noexcept override;
};

#endif // BIFF_FILES_H
