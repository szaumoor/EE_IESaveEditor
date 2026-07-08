#ifndef EESAVEEDITOR_TLK_H
#define EESAVEEDITOR_TLK_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#include <type_traits>

#pragma pack(push, 1)

struct TlkFileHeader
{
    CharArray<4> signature; // "TLK "
    CharArray<4> version; // "V1  "
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

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<TlkFileHeader> );
static_assert( std::is_standard_layout_v<TlkFileHeader> );
static_assert( sizeof( TlkFileHeader ) == 18, "TlkFileHeader size is incorrect" );

static_assert( std::is_trivially_copyable_v<TlkFileEntry> );
static_assert( std::is_standard_layout_v<TlkFileEntry> );
static_assert( sizeof( TlkFileEntry ) == 26, "TlkFileEntry size is incorrect" );

#pragma endregion

#endif //EESAVEEDITOR_TLK_H
