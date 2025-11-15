#ifndef IE_FILES_H
#define IE_FILES_H

#include <string>



enum class [[nodiscard]] IEFileState
{
    Unreadable,
    Readable,
    ReadableButMalformed,
    ReadableAndValid
};

class IEFile
{
public:
    virtual ~IEFile() = default;

    IEFileState get_state() const noexcept { return state; }
    [[nodiscard]] bool good() const noexcept { return state == IEFileState::ReadableAndValid; }
    explicit operator bool() const noexcept { return good(); }

    IEFile() = delete;

    [[nodiscard]] const std::string& get_path() const noexcept { return path; }

protected:
    explicit IEFile(const char* path) : path(std::string(path)) {}
    IEFileState state = IEFileState::Unreadable;
    virtual void check_for_malformation() = 0;

private:
    const std::string path;
};


#endif // IE_FILES_H