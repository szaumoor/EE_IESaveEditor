#ifndef EE_SAVEEDITOR_BMP_H
#define EE_SAVEEDITOR_BMP_H

#include "../utils/aliases.h"
#include "../utils/helper_structs.h"

#pragma pack(push, 1)

struct BmpFileHeader
{
    CharArray<2>  signature;          // 0x0000  "BM"
    u32           file_size;          // 0x0002  total file size (bytes)
    u16           reserved1;          // 0x0006  must be 0
    u16           reserved2;          // 0x0008  must be 0
    u32           raster_data_offset; // 0x000A  offset to pixel array
};

enum struct BmpHeaderSize : u32
{
    Os2 = 12, v3 = 40, v4 = 108, v5 = 140
};

struct BmpOs2Header
{
    BmpHeaderSize header_size; // 0x00 = 12

    u16 width;                 // 0x04
    u16 height;                // 0x06
    u16 planes;                // 0x08
    u16 bits_per_pixel;        // 0x0A
};

struct BmpV3Header
{
    BmpHeaderSize header_size; // 0x00  = 40

    i32 width;                 // 0x04
    i32 height;                // 0x08
    u16 planes;                // 0x0C
    u16 bits_per_pixel;        // 0x0E
    u32 compression;           // 0x10
    u32 image_size;            // 0x14
    u32 x_pixels_per_meter;    // 0x18
    u32 y_pixels_per_meter;    // 0x1C
    u32 colors_used;           // 0x20
    u32 colors_important;      // 0x24
};

struct BmpV4Header
{
    BmpHeaderSize header_size;           // 0x00  = 108

    i32 width;                 // 0x04
    i32 height;                // 0x08
    u16 planes;                // 0x0C
    u16 bits_per_pixel;        // 0x0E
    u32 compression;           // 0x10
    u32 image_size;            // 0x14
    i32 x_pixels_per_meter;    // 0x18
    i32 y_pixels_per_meter;    // 0x1C
    u32 colors_used;           // 0x20
    u32 colors_important;      // 0x24

    u32 red_mask;              // 0x28
    u32 green_mask;            // 0x2C
    u32 blue_mask;             // 0x30
    u32 alpha_mask;            // 0x34
    u32 color_space_type;      // 0x38
    i32 red_x;                 // 0x3C
    i32 red_y;                 // 0x40
    i32 red_z;                 // 0x44
    i32 green_x;               // 0x48
    i32 green_y;               // 0x4C
    i32 green_z;               // 0x50
    i32 blue_x;                // 0x54
    i32 blue_y;                // 0x58
    i32 blue_z;                // 0x5C
    u32 gamma_red;             // 0x60
    u32 gamma_green;           // 0x64
    u32 gamma_blue;            // 0x68
};

struct BmpV5Header
{
    // ---- v4 base ----
    u32 header_size;           // 0x00  = 124
    i32 width;                 // 0x04
    i32 height;                // 0x08
    u16 planes;                // 0x0C
    u16 bits_per_pixel;        // 0x0E
    u32 compression;           // 0x10
    u32 image_size;            // 0x14
    i32 x_pixels_per_meter;    // 0x18
    i32 y_pixels_per_meter;    // 0x1C
    u32 colors_used;           // 0x20
    u32 colors_important;      // 0x24
    u32 red_mask;              // 0x28
    u32 green_mask;            // 0x2C
    u32 blue_mask;             // 0x30
    u32 alpha_mask;            // 0x34
    u32 color_space_type;      // 0x38
    i32 red_x;                 // 0x3C
    i32 red_y;                 // 0x40
    i32 red_z;                 // 0x44
    i32 green_x;               // 0x48
    i32 green_y;               // 0x4C
    i32 green_z;               // 0x50
    i32 blue_x;                // 0x54
    i32 blue_y;                // 0x58
    i32 blue_z;                // 0x5C
    u32 gamma_red;             // 0x60
    u32 gamma_green;           // 0x64
    u32 gamma_blue;            // 0x68

    // v5
    u32 intent;                // 0x6C
    u32 profile_data;          // 0x70
    u32 profile_size;          // 0x74
    u32 reserved;              // 0x78
};

#pragma pack(pop)

static_assert(sizeof(BmpFileHeader) == 0x0E);
static_assert(sizeof(BmpOs2Header) == 12);
static_assert(sizeof(BmpV3Header) == 40);
static_assert(sizeof(BmpV5Header) == 124);

#endif //EE_SAVEEDITOR_BMP_H