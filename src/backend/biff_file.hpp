#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "ie_files.hpp"
#include "binary_layouts/itm.hpp"
#include "binary_layouts/key_biff.hpp"
#include "binary_layouts/spl.hpp"

#include <string_view>
#include <vector>


class BiffFile final : public IEClass
{
public:
    static Possible<BiffFile> open( std::string_view path );
    void check_for_malformation() noexcept;
    [[nodiscard]] bool good() const noexcept { return m_good; }
    [[nodiscard]] std::string_view path() const noexcept { return m_path; }
    explicit operator bool() const noexcept { return m_good; }

private:
    explicit BiffFile(std::string_view path) : m_path(path) {}

    BiffHeader m_header{};
    std::vector<FileEntry> m_file_entries;
    std::vector<TileEntry> m_tile_entries;

    std::vector<SplHeader> m_spells;
    std::vector<ItmHeader> m_itms;
    std::vector<std::string> m_ids_files;
    std::vector<std::string> m_ini_files;

    bool m_good = false;
    std::string m_path;
};

static_assert(IE_Openable<BiffFile>);

#endif // BIFF_FILES_H
