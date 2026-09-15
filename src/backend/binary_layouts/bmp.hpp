#ifndef EE_SAVEEDITOR_BMP_H
#define EE_SAVEEDITOR_BMP_H

#include "../utils/aliases.hpp"
#include "../utils/helper_structs.hpp"

#include <type_traits>

#pragma pack(push, 1)

enum struct BmpHeaderSize : u32
{
    v3 = 40, v4 = 108, v5 = 124
};

struct BmpFileHeader
{
    CharArray<2>  signature;
    u32           file_size;
    u16           reserved1;
    u16           reserved2;
    u32           raster_data_offset;
};

struct BmpOs2Header
{
    u32 header_size;
    u16 width;
    u16 height;
    u16 planes;
    u16 bits_per_pixel;
};

struct BmpV3Header
{
    u32 header_size;

    i32 width;
    i32 height;
    u16 planes;
    u16 bits_per_pixel;

    u32 compression;
    u32 image_size;

    i32 x_pixels_per_meter;
    i32 y_pixels_per_meter;

    u32 colors_used;
    u32 colors_important;
};

struct BmpV4Header
{
    u32 header_size;

    i32 width;
    i32 height;
    u16 planes;
    u16 bits_per_pixel;

    u32 compression;
    u32 image_size;
    i32 x_pixels_per_meter;
    i32 y_pixels_per_meter;
    u32 colors_used;
    u32 colors_important;

    u32 red_mask;
    u32 green_mask;
    u32 blue_mask;
    u32 alpha_mask;
    u32 color_space_type;
    i32 red_x;
    i32 red_y;
    i32 red_z;
    i32 green_x;
    i32 green_y;
    i32 green_z;
    i32 blue_x;
    i32 blue_y;
    i32 blue_z;
    u32 gamma_red;
    u32 gamma_green;
    u32 gamma_blue;
};

struct BmpV5Header
{
    u32 header_size;
    i32 width;
    i32 height;
    u16 planes;
    u16 bits_per_pixel;

    u32 compression;
    u32 image_size;
    i32 x_pixels_per_meter;
    i32 y_pixels_per_meter;
    u32 colors_used;
    u32 colors_important;

    u32 red_mask;
    u32 green_mask;
    u32 blue_mask;
    u32 alpha_mask;
    u32 color_space_type;

    i32 red_x;
    i32 red_y;
    i32 red_z;
    i32 green_x;
    i32 green_y;
    i32 green_z;
    i32 blue_x;
    i32 blue_y;
    i32 blue_z;

    u32 gamma_red;
    u32 gamma_green;
    u32 gamma_blue;

    u32 intent;
    u32 profile_data;
    u32 profile_size;
    u32 reserved;
};

#pragma pack(pop)

#pragma region Asserts

static_assert( std::is_trivially_copyable_v<BmpFileHeader> );
static_assert( std::is_standard_layout_v<BmpFileHeader> );
static_assert(sizeof(BmpFileHeader) == 14);

static_assert( std::is_trivially_copyable_v<BmpOs2Header> );
static_assert( std::is_standard_layout_v<BmpOs2Header> );
static_assert(sizeof(BmpOs2Header) == 12);

static_assert( std::is_trivially_copyable_v<BmpV3Header> );
static_assert( std::is_standard_layout_v<BmpV3Header> );
static_assert(sizeof(BmpV3Header) == 40);

static_assert( std::is_trivially_copyable_v<BmpV4Header> );
static_assert( std::is_standard_layout_v<BmpV4Header> );
static_assert(sizeof(BmpV4Header) == 108);

static_assert( std::is_trivially_copyable_v<BmpV5Header> );
static_assert( std::is_standard_layout_v<BmpV5Header> );
static_assert(sizeof(BmpV5Header) == 124);

#pragma endregion

#endif
