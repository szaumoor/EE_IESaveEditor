#ifndef XREF_FILE_H
#define XREF_FILE_H

#include "aliases.h"
#include <string>

#pragma pack(push, 1)
struct Strref
{
    u32 value;
};
#pragma pack(pop)

#pragma pack(push, 1)
template<u32 Length>
struct CharArray
{
    char value[Length];
    std::string to_string() const
    {
        return std::string(value, Length);
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Resref
{
    CharArray<8> value;
    std::string to_string() const
    {
        return value.to_string();
    }
};
#pragma pack(pop)

#endif