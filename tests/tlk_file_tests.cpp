#include <gtest/gtest.h>

#include <expected>
#include <filesystem>
#include <fstream>

#include "../src/backend/tlk_file.h"
#include "../src/backend/ie_files.h"


using namespace std;

constexpr auto real_path = "../tests/res/dialog.tlk";

TEST( TlkFileTest, TlkIsUnreadableTest )
{
    EXPECT_TRUE( TlkFile( "nonexistent.tlk" ).unreadable() );
}

TEST( TlkFileTest, TlkStringCountZeroIfInvalid )
{
    const auto tlk = TlkFile( "nonexistent.tlk" );
    EXPECT_TRUE( tlk.unreadable() && tlk.length() == 0 );
}

TEST( TlkFileTest, TlkIsMalformedVersion )
{
    ofstream ofs( "invalid_version.tlk", ios::binary);
    ofs.write("TLK ", 4); // Valid signature
    ofs.write( "Invl", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_version.tlk" ).malformed() );
    filesystem::remove( "invalid_version.tlk" );
}

TEST( TlkFileTest, TlkIsMalformedSignature )
{
    ofstream ofs( "invalid_signature.tlk", ios::binary );
    ofs.write( "XXXX", 4 ); // Invalid signature
    ofs.write( "V1  ", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_signature.tlk" ).malformed() );
    filesystem::remove( "invalid_signature.tlk" );
}

TEST( TlkFileTest, TlkIsReadableAndValid )
{
    ofstream ofs( "valid_tlk.tlk", ios::binary );
    ofs.write( "TLK ", 4 ); // Valid signature
    ofs.write( "V1  ", 4 ); // Valid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "valid_tlk.tlk" ).good() );
    filesystem::remove( "valid_tlk.tlk" );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOne )
{
    const TlkFile tlk( real_path );
    EXPECT_TRUE( tlk.good() );
    const auto result = tlk.at_index( 1 );
    EXPECT_TRUE( result.has_value() );
    EXPECT_TRUE( *result == "No, I'm sorry, none of them sound familiar." );
}

TEST( TlkFileTest, TlkHasCantAccessInvalidIndexes)
{
    const TlkFile tlk( real_path );
    EXPECT_TRUE( tlk.good() );
    const auto result1 = tlk.at_index( -1 );
    const auto result2 = tlk.at_index( tlk.length() );
    EXPECT_TRUE( !result1.has_value() && !result2.has_value() );
}

TEST( TlkFileTest, TlkReturnsUnexpectedIfFileIsMalformed )
{
    ofstream ofs0( "invalid_signature0.tlk", ios::binary );
    ofs0.write( "XXXX", 4 ); // Invalid signature
    ofs0.write( "V1  ", 4 ); // Valid version
    ofs0.close();
    ofstream ofs1( "invalid_signature1.tlk", ios::binary );
    ofs1.write( "TLK ", 4 ); // Invalid signature
    ofs1.write( "Invl", 4 ); // Valid version
    ofs1.close();
    const auto tlk0 = TlkFile( "invalid_signature0.tlk");
    EXPECT_FALSE( tlk0.at_index(1).has_value() );
    const auto tlk1 = TlkFile( "invalid_signature1.tlk");
    EXPECT_FALSE( tlk1.at_index(1).has_value() );
    filesystem::remove( "invalid_signature0.tlk" );
    filesystem::remove( "invalid_signature1.tlk" );
}
