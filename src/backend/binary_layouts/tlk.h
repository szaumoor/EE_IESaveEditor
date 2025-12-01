#ifndef EESAVEEDITOR_TLK_H
#define EESAVEEDITOR_TLK_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#pragma pack(push, 1)

struct TlkFileHeader
{
    CharArray<4> signature; // "TLK "
    CharArray<4> version;   // "V1  "
    u16 language_id;
    u32 entry_count;
    u32 offset_to_str_data;
};

struct TlkFileEntry
{
    u16 entry_flags;
    CharArray<8> resref;
    u32 volume;
    u32 pitch;
    u32 offset_to_string;
    u32 string_length;
};

#pragma pack(pop)

static_assert(sizeof(TlkFileHeader) == 18, "TlkFileHeader size is incorrect");
static_assert(sizeof(TlkFileEntry) == 26, "TlkFileEntry size is incorrect");

#endif //EESAVEEDITOR_TLK_H