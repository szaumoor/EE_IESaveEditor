#ifndef HELPER_STRUCTS_H
#define HELPER_STRUCTS_H

#include "aliases.h"

#include <string>

using Strref = u32;

#pragma pack(push, 1)
template<u32 Length>
struct CharArray
{
    char value[Length];

    [[nodiscard]]
    std::string to_string() const {
        return trim_nulls(std::move(std::string(value, Length)));
    }

private:
    static std::string trim_nulls(std::string&& str) {
        if (const auto null_pos = str.find_first_of('\0'); null_pos != std::string::npos)
            str.resize(null_pos);
        return str;
    }
};

struct Resref
{
    CharArray<8> value;

    [[nodiscard]]
    std::string to_string() const { return value.to_string(); }
};
#pragma pack(pop)

#endif // HELPER_STRUCTS_H