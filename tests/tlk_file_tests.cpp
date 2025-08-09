#include "../src/tlk_file.h"
#include "../src/ie_files.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <optional>
#include <iostream>

using namespace std;

TEST( TlkFileTest, TlkIsUnreadableTest )
{
    EXPECT_TRUE( TlkFile( "nonexistent.tlk" ).get_state() ==
        IEFileState::Unreadable);
}

TEST( TlkFileTest, TlkIsMalformedVersion )
{
    ofstream ofs( "invalid_version.tlk", ios::binary);
    ofs.write("TLK ", 4); // Valid signature
    ofs.write( "Invl", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_version.tlk" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_version.tlk" );
}

TEST( TlkFileTest, TlkIsMalformedSignature )
{
    ofstream ofs( "invalid_signature.tlk", ios::binary );
    ofs.write( "XXXX", 4 ); // Invalid signature
    ofs.write( "V1  ", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_signature.tlk" ).get_state() ==
        IEFileState::ReadableButMalformed );
    filesystem::remove( "invalid_signature.tlk" );
}

TEST( TlkFileTest, TlkIsReadableAndValid ) {
    TlkFile tlk( "dialog.tlk" );
    EXPECT_EQ( tlk.get_state(), IEFileState::ReadableAndValid );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOne )
{
    TlkFile tlk( "dialog.tlk" );
    EXPECT_EQ( tlk.get_state(), IEFileState::ReadableAndValid);
    const auto result = tlk.at_index( 1 );
    EXPECT_TRUE( result.has_value() );
    EXPECT_TRUE( *result == "No, I'm sorry, none of them sound familiar." );
}
