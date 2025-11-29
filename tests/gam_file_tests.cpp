#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/backend/ie_files.h"
#include "../src/backend/gam_file.h"

using namespace std;

// class GamFileTests : public ::testing::Test {
// protected:
//     const char* path = "invalid_version.gam";
//
//
//     void TearDown() override {
//         std::error_code ec;
//         std::filesystem::remove(filesystem::path(path), ec);
//     }
// };

constexpr auto real_gam = "../tests/res/BALDUR.gam";

auto gam_with(const char* name, const char* signature, const char* version) -> void {
    ofstream ofs( name, ios::binary );
    ofs.write( signature, 4 );
    ofs.write( version, 4 );
    ofs.close();
}

TEST( GamFileTests, GamIsUnreadableTest )
{
    EXPECT_TRUE( GamFile("nonexistent.gam").unreadable() );
}

TEST( GamFileTests, GamIsMalformedVersion )
{
    const auto path = "invalid_version.gam";
    gam_with(path, "GAME", "Invl");

    EXPECT_TRUE( GamFile(path).malformed() );
    filesystem::remove( filesystem::path(path) );
}

TEST( GamFileTests, RealGamIsReadableAndValid )
{
    EXPECT_TRUE( GamFile( real_gam ).good() );
}

TEST( GamFileTests, GamIsReadableAndValid )
{
    const auto path = "valid_version.gam";
    gam_with(path, "GAME", "V2.0");

    EXPECT_TRUE( GamFile( path ).good() );
    filesystem::remove( path );
}

TEST( GamFileTests, GamIsReadableAndValidTwoPointOne )
{
    const auto path = "valid_version.gam";
    gam_with(path, "GAME", "V2.1");

    EXPECT_TRUE( GamFile( path ).good() );
    filesystem::remove( path );
}

TEST( GamFileTests, GamIsMalformedSignature )
{
    const auto path = "invalid_signature.gam";
    gam_with(path, "XXXX", "V2.0");
    EXPECT_TRUE( GamFile( path ).malformed() );
    filesystem::remove( path );
}

TEST( GamFileTests, GamHasAtLeastOnePartyMember )
{
    const GamFile gam( real_gam );
    EXPECT_TRUE( gam.good() );
    EXPECT_GT(gam._party_members.size(),1);
}