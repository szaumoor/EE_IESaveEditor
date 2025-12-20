#ifndef IE_FILES_H
#define IE_FILES_H

#include <string_view>

class IEFile
{
public:
    virtual ~IEFile() = default;

    [[nodiscard]] explicit operator bool() const noexcept
    {
        return m_good;
    }

protected:
    explicit IEFile( const std::string_view path ) : m_path( path ) { }

    virtual void check_for_malformation() noexcept = 0;

    bool m_good = false;
    const std::string_view m_path;
};


#endif // IE_FILES_H
