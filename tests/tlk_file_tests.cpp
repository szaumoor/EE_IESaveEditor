#include <gtest/gtest.h>

#include <expected>
#include <filesystem>
#include <fstream>

#include "../src/backend/tlk_file.h"
#include "../src/backend/ie_files.h"

#include "utils/tests_helper.h"

constexpr auto real_path = "../tests/res/dialog.tlk";

TEST( TlkFileTest, TlkIsUnreadableTest )
{
    ASSERT_TRUE( TlkFile( "nonexistent.tlk" ).unreadable() );
}

TEST( TlkFileTest, TlkStringCountZeroIfInvalid )
{
    const auto tlk = TlkFile( "nonexistent.tlk" );
    ASSERT_TRUE( tlk.unreadable() && tlk.length() == 0 );
}

TEST( TlkFileTest, TlkIsMalformedVersion )
{
    const TempCreator temp( "invalid_version.tlk", "TLK ", "Invl" );
    ASSERT_TRUE( TlkFile( temp.name ).malformed() );
}

TEST( TlkFileTest, TlkIsMalformedSignature )
{
    const TempCreator temp( "invalid_signature.tlk", "XXXX", "V1  " );
    ASSERT_TRUE( TlkFile( temp.name ).malformed() );
}

TEST( TlkFileTest, TlkIsReadableAndValid )
{
    const TempCreator temp( "valid_tlk.tlk", "TLK ", "V1  " );
    ASSERT_TRUE( TlkFile( temp.name ).good() );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOne )
{
    const TlkFile tlk( real_path );
    ASSERT_TRUE( tlk.good() );

    const auto result = tlk.at_index( 1 );
    ASSERT_TRUE( result.has_value() );
    ASSERT_TRUE( *result == "No, I'm sorry, none of them sound familiar." );
}

TEST( TlkFileTest, TlkHasCantAccessInvalidIndexes)
{
    const TlkFile tlk( real_path );
    ASSERT_TRUE( tlk.good() );

    const auto result1 = tlk.at_index( -1 );
    const auto result2 = tlk.at_index( tlk.length() );
    ASSERT_TRUE( !result1.has_value() && !result2.has_value() );
}

TEST( TlkFileTest, TlkReturnsUnexpectedIfFileIsMalformed )
{
    const TempCreator temp0( "invalid_version.tlk", "XXXX", "V1  " );
    const TlkFile tlk0( temp0.name);
    EXPECT_FALSE(tlk0.at_index(1).has_value());

    const TempCreator temp1("invalid_signature1.tlk", "TLK ", "Invl");
    const TlkFile tlk1( temp1.name);
    ASSERT_FALSE( tlk1.at_index(1).has_value() );
}
