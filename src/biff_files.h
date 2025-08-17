#ifndef BIFF_FILES_H
#define BIFF_FILES_H

#include "aliases.h"
#include "helper_structs.h"

namespace {
    enum ResourceType : i16
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

    #pragma pack(push, 1)
    struct BiffHeader
    {
        CharArray<4> signature;
        CharArray<4> version;
        u32 count_of_fileset_entries;
        u32 count_of_tileset_entries;
        u32 offset_to_fileset_entries;
    };

    struct FilesetEntry
    {
        u32 resource_locator;
        u32 offset;
        u32 size;
        ResourceType resource_type;
        u16 unknown;
    };

    struct TilesetEntry
    {
        u32 resource_locator;
        u32 offset;
        u32 tile_count;
        u32 tile_size;
        ResourceType resource_type;
        u16 unknown;
    };
    #pragma pack(pop)
}

template <u32 X, u32 Y, u32 Z>
struct BiffFile
{
    BiffHeader header;
    FilesetEntry fileset_entries[X];
    TilesetEntry tileset_entries[Y];
    char data[Z];
};

#endif // BIFF_FILES_H
