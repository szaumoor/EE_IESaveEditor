#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/backend/ie_files.h"
#include "../src/backend/key_file.h"

using namespace std;


TEST( KeyFileTest, KeyStructsHaveExpectedSize ) {
    EXPECT_TRUE( sizeof( KeyFileHeader ) == 24 );
    EXPECT_TRUE( sizeof( BiffEntry ) == 12 );
    EXPECT_TRUE( sizeof( ResourceEntry ) == 14 );
}

TEST( KeyFileTest, KeyIsUnreadableTest ) {
    EXPECT_TRUE( KeyFile( "nonexistent.key" ).get_state() ==
        IEFileState::Unreadable );
}

TEST( KeyFileTest, KeyBiffCountZeroIfInvalid ) {
    const auto key = KeyFile( "nonexistent.key" );
    EXPECT_TRUE( key.get_state() == IEFileState::Unreadable &&
        key.biff_count() == 0 );
}

TEST( KeyFileTest, KeyResCountZeroIfInvalid ) {
    const auto key = KeyFile( "nonexistent.key" );
    EXPECT_TRUE( key.get_state() == IEFileState::Unreadable &&
        key.resource_count() == 0 );
}

TEST( KeyFileTest, KeyIsMalformedVersion ) {
    ofstream ofs( "invalid_version.key", ios::binary );
    ofs.write( "KEY ", 4 ); // Valid signature
    ofs.write( "Invl", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( KeyFile( "invalid_version.key" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_version.key" );
}

TEST( KeyFileTest, KeyIsMalformedSignature ) {
    ofstream ofs( "invalid_signature.key", ios::binary );
    ofs.write( "XXXX", 4 ); // Invalid signature
    ofs.write( "V1  ", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( KeyFile( "invalid_signature.key" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_signature.key" );
}

TEST( KeyFileTest, RealKeyIsReadableAndValid ) {
    const KeyFile key( "chitin.key" );
    EXPECT_EQ( key.get_state(), IEFileState::ReadableAndValid );
}

TEST( KeyFileTest, KeyIsReadableAndValid ) {
    ofstream ofs( "valid_key.key", ios::binary );
    ofs.write( "KEY ", 4 ); // Valid signature
    ofs.write( "V1  ", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( KeyFile( "valid_key.key" ).get_state() ==
        IEFileState::ReadableAndValid );
    filesystem::remove( "valid_key.key" );
}