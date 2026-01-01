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
    reader.into(header_size, sizeof(bmp_header));
    switch (header_size)
    {
        case BmpHeaderSize::Os2:
        {
            BmpOs2Header os2_header{};
            reader.into( os2_header, sizeof(bmp_header) );
            break;
        }
        case BmpHeaderSize::v3:
        {
            BmpV3Header v3_header{};
            reader.into( v3_header, sizeof(bmp_header) );
            break;
        }
        case BmpHeaderSize::v4:
        {
            BmpV4Header v4_header{};
            reader.into( v4_header, sizeof(bmp_header) );
            break;
        }
        case BmpHeaderSize::v5:
        {
            BmpV5Header v5_header{};
            reader.into( v5_header, sizeof(bmp_header) );
            break;
        }
    }
    ASSERT_TRUE(true);
}