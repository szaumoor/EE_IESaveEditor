#ifndef EESAVEEDITOR_KEY_BIFF_H
#define EESAVEEDITOR_KEY_BIFF_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

enum ResourceType : u16
{
    NotFound      = 0x0000,
    FileTypeBmp   = 0x0001,
    FileTypeMve   = 0x0002,
    FileTypeWav   = 0x0004,
    FileTypeWfx   = 0x0005,
    FileTypePlt   = 0x0006,
    FileTypeBam   = 0x03e8,
    FileTypeWed   = 0x03e9,
    FileTypeChu   = 0x03ea,
    FileTypeTi    = 0x03eb,
    FileTypeMos   = 0x03ec,
    FileTypeItm   = 0x03ed,
    FileTypeSpl   = 0x03ee,
    FileTypeBcs   = 0x03ef,
    FileTypeIds   = 0x03f0,
    FileTypeCre   = 0x03f1,
    FileTypeAre   = 0x03f2,
    FileTypeDlg   = 0x03f3,
    FileType2da   = 0x03f4,
    FileTypeGam   = 0x03f5,
    FileTypeSto   = 0x03f6,
    FileTypeWmap  = 0x03f7,
    FileTypeChr1  = 0x03f8,
    FileTypeEff   = 0x03f8,
    FileTypeBs    = 0x03f9,
    FileTypeChr   = 0x03fa,
    FileTypeVvc   = 0x03fb,
    FileTypeVef   = 0x03fc,
    FileTypePro   = 0x03fd,
    FileTypeBio   = 0x03fe,
    FileTypeWbm   = 0x03ff,
    FileTypeFnt   = 0x0400,
    FileTypeGui   = 0x0402,
    FileTypeSql   = 0x0403,
    FileTypePvrz  = 0x0404,
    FileTypeGlsl  = 0x0405,
    FileTypeTlk   = 0x0407,
    FileTypeMenu  = 0x0408,
    FileTypeMenu2 = 0x0409,
    FileTypeTtf   = 0x040a,
    FileTypePng   = 0x040b,
    FileTypeBah   = 0x044c,
    FileTypeIni   = 0x0802,
    FileTypeSrc   = 0x0803
};

static_assert(sizeof(ResourceType) == 2, "ResourceType size is incorrect");

#pragma pack(push, 1)

struct BiffHeader
{
    CharArray<4> signature; // "BIFF"
    CharArray<4> version;   // "V1  "
    u32 count_of_file_entries;
    u32 count_of_tile_entries;
    u32 offset_to_file_entries;
};

struct FileEntry
{
    u32 resource_locator;
    u32 offset;
    u32 size;
    ResourceType resource_type;
    u16 unknown;
};

struct TileEntry
{
    u32 resource_locator;
    u32 offset_resource_data;
    u32 tile_count;
    u32 tile_size;
    ResourceType resource_type;
    u16 unknown;
};

struct KeyFileHeader
{
    CharArray<4> signature; // "KEY "
    CharArray<4> version;   // "V1  "
    u32 biff_count;
    u32 resource_count;
    u32 offset_to_biff_entries;
    u32 offset_to_resource_entries;
};

struct BiffEntry
{
    u32 length_biff_file;
    u32 offset_to_biff_filename;
    u16 length_biff_filename_with_null;
    u16 location_file_bitfield;
};

struct ResourceEntry
{
    Resref resource_name;
    u16 resource_type;
    u32 resource_locator;
};

#pragma pack(pop)


static_assert(sizeof(BiffHeader) == 20, "BiffHeader size is incorrect");
static_assert(sizeof(BiffEntry) == 12, "BiffEntry size is incorrect");
static_assert(sizeof(ResourceEntry) == 14, "ResourceEntry size is incorrect");
static_assert(sizeof(KeyFileHeader) == 24, "KeyFileHeader size is incorrect");

#endif //EESAVEEDITOR_KEY_BIFF_H