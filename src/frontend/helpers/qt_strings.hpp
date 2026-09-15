#ifndef EE_SAVEEDITOR_QT_STRINGS_H
#define EE_SAVEEDITOR_QT_STRINGS_H

#include <QString>
#include <string>
#include <string_view>

#include "../../backend/utils/errors.hpp"
#include "../../backend/utils/helper_structs.hpp"
#include "../../backend/utils/ie_string.hpp"

namespace str
{
    inline QString from(const std::string& str) noexcept
    {
        return QString::fromStdString(str);
    }

    inline QString from(const char* str) noexcept
    {
        return QString::fromUtf8(str);
    }

    inline QString from( const std::string_view str) noexcept
    {
        return QString::fromUtf8( str.data(),
            static_cast<qsizetype>(str.size()) );
    }

    inline QString from(const IEStringView& str) noexcept
    {
        return QString::fromStdString( str.std_string() );
    }

    template<u32 Length>
    QString from(const CharArray<Length>& str) noexcept
    {
        const auto* end = std::find(str.value, str.value + Length, '\0');
        return QString::fromUtf8(
            str.value,
            static_cast<qsizetype>(end - str.value)
        );
    }

    inline QString from(const IEError& err) noexcept
    {
        return from(err.what());
    }

}

#endif //EE_SAVEEDITOR_QT_STRINGS_H
