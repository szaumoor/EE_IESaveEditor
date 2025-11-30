#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/backend/ie_files.h"
#include "../src/backend/gam_file.h"

#include "utils/tests_helper.h"

constexpr auto real_gam = "../tests/res/BALDUR.gam";


TEST( GamFileTests, GamIsUnreadableTest )
{
    ASSERT_TRUE( GamFile("nonexistent.gam").unreadable() );
}

TEST( GamFileTests, GamIsMalformedVersion )
{
    const auto temp = TempCreator("invalid_version.gam", "GAME", "Invl");
    ASSERT_TRUE( GamFile(temp.name).malformed() );
}

TEST( GamFileTests, RealGamIsReadableAndValid )
{
    ASSERT_TRUE( GamFile( real_gam ).good() );
}

TEST( GamFileTests, GamIsReadableAndValid )
{
    const auto temp = TempCreator("valid_version.gam", "GAME", "V2.0");
    ASSERT_TRUE( GamFile( temp.name ).good() );
}

TEST( GamFileTests, GamIsReadableAndValidTwoPointOne )
{
    const auto temp = TempCreator("valid_version.gam", "GAME", "V2.1");
    ASSERT_TRUE( GamFile( temp.name ).good() );
}

TEST( GamFileTests, GamIsMalformedSignature )
{
    const auto temp = TempCreator("invalid_signature.gam", "XXXX", "V2.0");
    ASSERT_TRUE( GamFile( temp.name ).malformed() );
}

TEST( GamFileTests, GamHasAtLeastOnePartyMember )
{
    const GamFile gam( real_gam );
    ASSERT_TRUE( gam.good() );
    ASSERT_GT(gam._party_members.size(),1);
}