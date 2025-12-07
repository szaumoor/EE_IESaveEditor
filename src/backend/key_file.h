#ifndef KEY_FILE_H
#define KEY_FILE_H

#include <expected>

#include "ie_files.h"
#include "binary_layouts/key_biff.h"

#include <string_view>
#include <vector>

#include "utils/errors.h"

class KeyFile;

using std::string_view;
using std::vector;
using PossibleKeyFile = std::expected<KeyFile, IEError>;

class KeyFile final : public IEFile
{
public:
    [[nodiscard]]
    static PossibleKeyFile open( string_view path ) noexcept;
private:
    explicit KeyFile( string_view path ) noexcept;
    KeyFileHeader _header{};
    vector<BiffEntry> _biff_entries;
    vector<ResourceEntry> _resource_entries;
    void check_for_malformation() noexcept override;
};

#endif // KEY_FILE_H