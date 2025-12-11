#include <gtest/gtest.h>

#include <string_view>

#include "../src/backend/biff_file.h"
#include "../src/backend/utils/errors.h"

#include "utils/tests_helper.h"

static constexpr std::string_view kRealBiff("../../tests/res/Spells.bif");
static constexpr std::string_view kRealBiffWithTilesets("../../tests/res/25ArMisc.bif");

TEST( BiffFileTests, BiffIsUnreadableTest )
{
    const auto biff = BiffFile::open("nonexistent.biff");
    ASSERT_TRUE( !biff && biff.error().type() == IEErrorType::Unreadable );
}

TEST( BiffFileTests, BiffIsMalformedVersion )
{
    const TempCreator temp("invalid_version.biff", "BIFF", "Invl");
    const auto biff = BiffFile::open(temp.name);
    ASSERT_TRUE( !biff && biff.error().type() == IEErrorType::Malformed );
}

TEST( BiffFileTests, BiffIsMalformedSig )
{
    const TempCreator temp("invalid_version.biff", "BUFF", "V1  ");
    const auto biff = BiffFile::open(temp.name);
    ASSERT_TRUE( !biff && biff.error().type() == IEErrorType::Malformed );
}

TEST( BiffFileTests, RealBiffIsReadableAndValid )
{
    ASSERT_TRUE( BiffFile::open( kRealBiff ).has_value() );
}

TEST( BiffFileTests, RealBiffWithTilesetsIsReadableAndValid )
{
    ASSERT_TRUE( BiffFile::open( kRealBiffWithTilesets ).has_value() );
}
