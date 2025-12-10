#ifndef IE_FILES_H
#define IE_FILES_H

#include <string_view>

class IEFile
{
public:
    virtual ~IEFile() = default;

    [[nodiscard]]
    explicit operator bool() const noexcept { return good; }

protected:
    explicit IEFile( const std::string_view path ) : _path( path ) { }
    bool good = false;

    virtual void check_for_malformation() noexcept = 0;

    const std::string_view _path;
};


#endif // IE_FILES_H
