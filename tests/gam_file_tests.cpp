#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string_view>

#include "../src/backend/gam_file.h"
#include "../src/backend/utils/errors.h"

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