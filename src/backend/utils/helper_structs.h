#ifndef HELPER_STRUCTS_H
#define HELPER_STRUCTS_H

#include "../utils/aliases.h"

#include <algorithm>
#include <string>

#pragma pack(push, 1)

/**
 * Parameterized char array to represent a char array in IE files.
 * Provides helper method to convert to a std::string which removes
 * all null characters.
 *
 * @tparam Length length of the array. Can only be up to 32 characters, fails to compile otherwise.
 */
template<u32 Length>
struct CharArray
{
    static_assert( Length > 0 and Length <= 32 );
    char value[Length];

    /**
     * Converts the char array to a std::string and trims the trailing null characters.
     *
     * @return std::string with the text in the char array
     */
    [[nodiscard]]
    std::string to_string() const
    {
        const auto* end = value + Length;
        const auto* null_pos = std::find(value, end, '\0');
        return std::string(value, null_pos);
    }

    [[nodiscard]]
    static std::optional<CharArray> from_string(std::string_view text) noexcept
    {
        if (text.size() > Length)
            return std::nullopt;

        CharArray result{};
        std::copy(text.begin(), text.end(), result.value);
        return result;
    }

    bool assign_string( const std::string_view text) noexcept {
        auto converted = from_string(text);

        if (!converted)
            return false;

        *this = *converted;
        return true;
    }
};

static_assert( sizeof( CharArray<32> ) == 32, "CharArray should be packed to fit in one byte per character" );

/**
 * Helper struct for the very commonly found 8-character resource reference in the IE files.
 * Provides helper method to convert to a std::string stripped of trailing null characters.
 */
struct Resref
{
    CharArray<8> value;

    /**
     * Converts the char array struct to a std::string and trims the trailing null characters.
     *
     * @return std::string with the text in the char array
     */
    [[nodiscard]]
    std::string to_string() const noexcept { return value.to_string(); }
};

#pragma pack(pop)

static_assert( sizeof( Resref ) == 8, "Resref struct no longer matches the expected size of 8 bytes" );

#endif // HELPER_STRUCTS_H
