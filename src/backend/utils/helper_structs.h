#ifndef HELPER_STRUCTS_H
#define HELPER_STRUCTS_H

#include "../utils/aliases.h"

#include <string>

using strref = u32;

#pragma pack(push, 1)

/**
 * Templatized char array to represent a char array in IE files.
 * Provides helper method to convert to a std::string which removes
 * all null characters.
 *
 * @tparam Length length of the array. Can only be up to 32 characters, fails to compile otherwise.
 */
template<u32 Length>
struct CharArray
{
    static_assert( Length <= 32 );
    char value[Length];

    /**
     * Converts the char array to a std::string and trims the trailing null characters.
     *
     * @return std::string with the text in the char array
     */
    [[nodiscard]]
    std::string to_string() const
    {
        return std::move( trim_nulls( std::string( value, Length ) ) );
    }

private:
    static std::string&& trim_nulls( std::string&& str ) noexcept
    {
        if ( const auto null_pos = str.find_first_of( '\0' ); null_pos != std::string::npos )
            str.resize( null_pos );
        return std::move( str );
    }
};

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
