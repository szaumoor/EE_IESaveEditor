#ifndef IE_FILES_H
#define IE_FILES_H

#include <string_view>

enum class [[nodiscard]] IEFileState
{
    Unread,
    Unreadable,
    Readable,
    Malformed,
    Valid
};

class IEFile
{
public:
    virtual ~IEFile() = default;

    [[nodiscard]] bool good() const noexcept { return state == IEFileState::Valid; }
    [[nodiscard]] bool bad() const noexcept { return !good(); }
    [[nodiscard]] bool malformed() const noexcept { return state == IEFileState::Malformed; }
    [[nodiscard]] bool unreadable() const noexcept { return state == IEFileState::Unreadable; }

    explicit operator bool() const noexcept { return good(); }

    IEFile() = delete;

protected:
    explicit IEFile(const std::string_view path ) : _path(path) {}

    IEFileState state = IEFileState::Unread;
    virtual void check_for_malformation() = 0;

private:
    const std::string_view _path;
};


#endif // IE_FILES_H