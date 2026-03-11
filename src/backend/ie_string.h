#ifndef EE_SAVEEDITOR_IE_STRING_H
#define EE_SAVEEDITOR_IE_STRING_H

#include <string_view>

#include "utils/aliases.h"

class IEStringView final
{
public:
    friend constexpr bool operator==(const IEStringView& lhs, const std::string_view rhs) noexcept
    {
        return lhs.m_view == rhs;
    }

    friend constexpr bool operator==( const std::string_view lhs, const IEStringView& rhs) noexcept
    {
        return lhs == rhs.m_view;
    }

    [[nodiscard]] constexpr std::string_view std_view() const { return m_view; }
    [[nodiscard]] constexpr u32 size() const { return m_view.length(); }
    [[nodiscard]] constexpr strref tlk_index() const { return m_tlk_index; }
private:
    friend class TlkFile;
    explicit constexpr IEStringView( const std::string_view view, const strref tlk_index) noexcept
        : m_view(view), m_tlk_index( tlk_index ) {}

    std::string_view m_view;
    strref m_tlk_index;
};

#endif //EE_SAVEEDITOR_IE_STRING_H