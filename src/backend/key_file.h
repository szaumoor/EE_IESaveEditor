#ifndef KEY_FILE_H
#define KEY_FILE_H

#include <expected>

#include "ie_files.h"
#include "binary_layouts/key_biff.h"

#include <string_view>
#include <vector>

class KeyFile;

using PossibleKeyFile = std::expected<KeyFile, IEError>;

class KeyFile final : public IEFile
{
public:
    static PossibleKeyFile open(std::string_view path) noexcept;
private:
    explicit KeyFile( std::string_view path ) noexcept;
    KeyFileHeader _header{};
    std::vector<BiffEntry> _biff_entries;
    std::vector<ResourceEntry> _resource_entries;
    void check_for_malformation() noexcept override;
};

#endif // KEY_FILE_H