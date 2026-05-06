#include <gtest/gtest.h>

#include <expected>
#include <string_view>

#include "../src/backend/tlk_file.h"
#include "../src/backend/utils/errors.h"

#include "utils/tests_helper.h"

static constexpr std::string_view kRealTlk( TEST_RES_DIR "/dialog.tlk" );
static const auto real_tlk = TlkFile::open( kRealTlk );

TEST( TlkFileTest, TlkIsUnreadableTest )
{
    const auto tlk = TlkFile::open( "nonexistent.tlk" );
    ASSERT_TRUE( not tlk && tlk.error().type() == IEErrorType::Unreadable );
}

TEST( TlkFileTest, TlkIsMalformedVersion )
{
    const TempCreator temp( "invalid_version.tlk", "TLK ", "Invl" );
    const auto tlk = TlkFile::open( temp.name );
    ASSERT_TRUE( not tlk && tlk.error().type() == IEErrorType::Malformed );
}

TEST( TlkFileTest, TlkIsMalformedSignature )
{
    const TempCreator temp( "invalid_signature.tlk", "XXXX", "V1  " );
    const auto tlk = TlkFile::open( temp.name );
    ASSERT_TRUE( not tlk && tlk.error().type() == IEErrorType::Malformed );
}

TEST( TlkFileTest, TlkIsReadableAndValid )
{
    const TempCreator temp( "valid_tlk.tlk", "TLK ", "V1  " );
    const auto tlk = TlkFile::open( temp.name );
    ASSERT_TRUE( tlk );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOne )
{
    ASSERT_TRUE( real_tlk.has_value() );
    const auto lookup = real_tlk->at( 1 );
    ASSERT_TRUE( lookup.has_value() );
    ASSERT_TRUE( *lookup == "No, I'm sorry, none of them sound familiar." );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOneWithBrackets )
{
    ASSERT_TRUE( real_tlk.has_value() );
    const auto lookup = ( *real_tlk )[1];
    ASSERT_TRUE( lookup.has_value() );
    ASSERT_TRUE( *lookup == "No, I'm sorry, none of them sound familiar." );
}

TEST( TlkFileTest, TlkHasCantAccessInvalidIndexes )
{
    ASSERT_TRUE( real_tlk.has_value() );
    const auto result1 = real_tlk->at( -1 );
    const auto result2 = real_tlk->at( real_tlk->length() );
    EXPECT_TRUE( !result1.has_value() );
    EXPECT_TRUE( !result2.has_value() );
}

TEST( TlkFileTest, CopyOwnsItsCachedStrings )
{
    const auto opened = TlkFile::open( kRealTlk );
    ASSERT_TRUE( opened.has_value() );

    const TlkFile& original = opened.value();
    const TlkFile copied( original );

    const auto original_lookup = original.at( 1 );
    const auto copied_lookup = copied.at( 1 );

    ASSERT_TRUE( original_lookup.has_value() );
    ASSERT_TRUE( copied_lookup.has_value() );
    EXPECT_EQ( copied_lookup->std_view(), original_lookup->std_view() );
    EXPECT_NE( copied_lookup->std_view().data(), original_lookup->std_view().data() );
}
