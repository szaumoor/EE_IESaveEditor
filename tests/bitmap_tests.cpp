#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string_view>

#include "../src/backend/binary_layouts/bmp.h"
#include "../src/backend/utils/io.h"

static constexpr std::string_view kRealBmp(TEST_RES_DIR "/sample_bitmap.bmp");

TEST( BitmapTests, BmpIsReadable )
{
    BmpFileHeader bmp_header{};
    std::ifstream file_handle(kRealBmp.data());
    const StructWriter reader(file_handle);
    reader.into( bmp_header );
    BmpHeaderSize header_size;
    reader.into( header_size, sizeof(BmpFileHeader) );
    ASSERT_TRUE(bmp_header.signature.to_string() == "BM" && header_size == BmpHeaderSize::v3);
}