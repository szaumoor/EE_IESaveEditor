#ifndef XREF_FILE_H
#define XREF_FILE_H

#include <cstdint>
#include <string>

#pragma pack(push, 1)
struct Strref
{
    int32_t value;
};
#pragma pack(pop)

#pragma pack(push, 1)
template<int Length>
struct CharArray
{
    char value[Length];
    std::string to_string() const
    {
        return std::string(value, Length);
    }
};
#pragma pack(pop)

#endif