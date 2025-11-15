#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/backend/ie_files.h"
#include "../src/backend/gam_file.h"


using namespace std;

TEST( GamFileTests, GamStructsHaveExpectedSize ) {
    EXPECT_TRUE( sizeof( GamHeader ) == 180 );
    EXPECT_TRUE( sizeof( GamCharacterStats ) == 116 );
    EXPECT_TRUE( sizeof( GamCharacterData ) == 352 );
    EXPECT_TRUE( sizeof( GamGlobalVariable ) == 84 );
    EXPECT_TRUE( sizeof( GamJournalEntry ) == 12 );
    EXPECT_TRUE( sizeof( GamFamiliarInfo ) == 400 );
    EXPECT_TRUE( sizeof( GamLocationInfo ) == 12 );
}

TEST( GamFileTests, GamIsUnreadableTest )
{
    EXPECT_TRUE( GamFile("nonexistent.gam").get_state()
        == IEFileState::Unreadable );
}

TEST( GamFileTests, GamIsMalformedVersion )
{
    ofstream ofs( "invalid_version.gam", ios::binary );
    ofs.write( "GAME", 4 ); // Valid signature
    ofs.write( "Invl", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( GamFile( "invalid_version.gam" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_version.gam" );
}

TEST( GamFileTests, RealGamIsReadableAndValid ) {
    const GamFile gam( "../BALDUR.gam" );
    EXPECT_EQ( gam.get_state(), IEFileState::ReadableAndValid );
}

TEST( GamFileTests, GamIsReadableAndValid ) {
    ofstream ofs( "valid_version.gam", ios::binary );
    ofs.write( "GAME", 4 ); // Valid signature
    ofs.write( "V2.0", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( GamFile( "valid_version.gam" ).get_state() ==
        IEFileState::ReadableAndValid );
    filesystem::remove( "valid_version.gam" );
}

TEST( GamFileTests, GamIsReadableAndValidTwoPointOne ) {
    ofstream ofs( "valid_version.gam", ios::binary );
    ofs.write( "GAME", 4 ); // Valid signature
    ofs.write( "V2.1", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( GamFile( "valid_version.gam" ).get_state() ==
        IEFileState::ReadableAndValid );
    filesystem::remove( "valid_version.gam" );
}

TEST( GamFileTests, GamIsMalformedSignature )
{
    ofstream ofs( "invalid_signature.gam", ios::binary );
    ofs.write( "XXXX", 4 ); // Invalid signature
    ofs.write( "V2.0", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( GamFile( "invalid_signature.gam" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_signature.gam" );
}

TEST( GamFileTests, GamHasAtLeastOnePartyMember )
{
    const GamFile gam( "../BALDUR.gam" );
    EXPECT_EQ( gam.get_state(), IEFileState::ReadableAndValid );
    auto& member = gam.party_members[0];
    std::cout << member.character_name.to_string() << '\n';
    std::cout <<  member.character_stats.in_party << '\n';
    EXPECT_GT(gam.party_members.size(),1);
}