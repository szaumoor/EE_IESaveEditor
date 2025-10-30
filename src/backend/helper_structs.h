#ifndef HELPER_STRUCTS_H
#define HELPER_STRUCTS_H

#include "aliases.h"

#include <string>

#pragma pack(push, 1)
struct Strref
{
    u32 value;

    [[nodiscard]]
    std::string to_string() const { return std::to_string(value); }
};

template<u32 Length>
struct CharArray
{
    char value[Length];

    [[nodiscard]]
    std::string to_string() const { return std::string(value, Length); }
};

struct Resref
{
    CharArray<8> value;

    [[nodiscard]]
    std::string to_string() const { return value.to_string(); }
};
#pragma pack(pop)

#endif // HELPER_STRUCTS_H