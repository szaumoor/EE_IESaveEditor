#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>

namespace rp::files
{
    enum class IEFileState
    {
        Unreadable,
        Readable,
        ReadableButMalformed,
        ReadableAndValid
    };

    class IEFile
    {
    private:
        const std::string path;
    protected:
        IEFile(const char* path) : path(std::string(path)) {}
        IEFileState state = IEFileState::Unreadable;
    public:
        IEFileState get_state() const noexcept { return state; }
        explicit operator bool() const noexcept { return state == IEFileState::ReadableAndValid; }
        const std::string& get_path() const noexcept { return path; }
        virtual void check_for_malformation() = 0;
    };

}

#endif // INTERFACES_H