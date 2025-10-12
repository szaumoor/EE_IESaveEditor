#ifndef IE_FILES_H
#define IE_FILES_H

#include <string>


namespace rp::files
{
    enum class [[nodiscard]] IEFileState
    {
        Unreadable,
        Readable,
        ReadableButMalformed,
        ReadableAndValid
    };

    class IEFile
    {
        const std::string path;
    protected:
        IEFile(const char* path) : path(std::string(path)) {}
        IEFileState state = IEFileState::Unreadable;
        virtual void check_for_malformation() = 0;
    public:
        virtual ~IEFile() = default;

        IEFileState get_state() const noexcept { return state; }
        explicit operator bool() const noexcept { return state == IEFileState::ReadableAndValid; }
        IEFile() = delete;

        [[nodiscard]]
        const std::string& get_path() const noexcept { return path; }
    };

}

#endif // IE_FILES_H