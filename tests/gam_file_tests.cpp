#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string_view>

#include "../src/backend/gam_file.h"
#include "../src/backend/utils/errors.h"
#include "../src/backend/utils/io.h"

#include "utils/tests_helper.h"

static constexpr std::string_view kRealGam("../tests/res/BALDUR.gam");

TEST( GamFileTests, GamIsUnreadableTest )
{
    const auto gam = GamFile::open("nonexistent.gam");
    ASSERT_TRUE( !gam && gam.error().type() == IEErrorType::Unreadable );
}

TEST( GamFileTests, GamIsMalformedVersion )
{
    const TempCreator temp("invalid_version.gam", "GAME", "Invl");
    const auto gam = GamFile::open(temp.name);
    ASSERT_TRUE( !gam && gam.error().type() == IEErrorType::Malformed );
}

TEST( GamFileTests, RealGamIsReadableAndValid )
{
    ASSERT_TRUE( GamFile::open( kRealGam ).has_value() );
}

TEST( GamFileTests, GamIsReadableAndValid )
{
    const TempCreator temp("valid_version.gam", "GAME", "V2.0");
    const auto gam = GamFile::open(temp.name);
    ASSERT_TRUE( gam.has_value() );
}

TEST( GamFileTests, GamIsReadableAndValidTwoPointOne )
{
    const TempCreator temp("valid_version.gam", "GAME", "V2.1");
    const auto gam = GamFile::open(temp.name);
    ASSERT_TRUE( gam.has_value() );
}

TEST( GamFileTests, GamIsMalformedSignature )
{
    const TempCreator temp("invalid_signature.gam", "XXXX", "V2.0");
    const auto gam = GamFile::open(temp.name);
    ASSERT_TRUE( !gam && gam.error().type() == IEErrorType::Malformed );
}

TEST(GamFileTests, GamHeaderCanBeWritten)
{
    const auto duplicate = "duplicate_gam.gam";
    std::filesystem::copy_file(kRealGam, duplicate);

    {
        const auto gam = GamFile::open(duplicate);
        EXPECT_TRUE(gam);
        auto real_gam = gam.value();
        EXPECT_TRUE(real_gam._header.party_gold == 180);
        real_gam._header.party_gold = 9999900;
        std::ofstream out(duplicate, std::ios::binary | std::ios::in | std::ios::out);
        const BinaryWriter writer(out);
        writer.out(real_gam._header);
        out.close();
    }

    const auto duplicate_gam = GamFile::open(duplicate);
    EXPECT_TRUE(duplicate_gam);
    const auto& real_duplicate_gam = duplicate_gam.value();
    EXPECT_TRUE(real_duplicate_gam._header.party_gold == 9999900);

    std::filesystem::remove("duplicate_gam.gam");
    EXPECT_TRUE(true);
}