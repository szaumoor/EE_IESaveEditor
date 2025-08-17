#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/ie_files.h"
#include "../src/gam_file.h"


using rp::files::IEFileState;
using namespace std;

//TEST( GamFileTests, GamIsUnreadableTest )
//{
//    EXPECT_TRUE( GamFile("nonexistent.gam").get_state()
//        == IEFileState::Unreadable );
//}
//
//TEST( GamFileTests, GamIsMalformedVersion )
//{
//    ofstream ofs( "invalid_version.gam", ios::binary );
//    ofs.write( "GAME", 4 ); // Valid signature
//    ofs.write( "Invl", 4 ); // Invalid version
//    ofs.close();
//    EXPECT_TRUE( GamFile( "invalid_version.gam" ).get_state() ==
//        IEFileState::ReadableButMalformed );
//    filesystem::remove( "invalid_version.gam" );
//}

TEST( GamFileTests, RealGamIsReadableAndValid ) {
    GamFile gam( "baldur.gam" );
    EXPECT_EQ( gam.get_state(), IEFileState::ReadableAndValid );
}

//TEST( GamFileTests, GamIsReadableAndValid ) {
//    ofstream ofs( "valid_version.gam", ios::binary );
//    ofs.write( "GAME", 4 ); // Valid signature
//    ofs.write( "V2.0", 4 ); // Invalid version
//    ofs.close();
//    EXPECT_TRUE( GamFile( "valid_version.gam" ).get_state() ==
//        IEFileState::ReadableAndValid );
//    filesystem::remove( "valid_version.gam" );
//}
//
//TEST( GamFileTests, GamIsMalformedSignature )
//{
//    ofstream ofs( "invalid_signature.gam", ios::binary );
//    ofs.write( "XXXX", 4 ); // Invalid signature
//    ofs.write( "V2.0", 4 ); // Valid version
//    ofs.close();
//    EXPECT_TRUE( GamFile( "invalid_signature.gam" ).get_state() ==
//        IEFileState::ReadableButMalformed );
//    filesystem::remove( "invalid_signature.gam" );
//}