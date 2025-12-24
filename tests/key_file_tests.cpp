#include <gtest/gtest.h>

#include <string_view>

#include "../src/backend/key_file.h"
#include "../src/backend/utils/errors.h"

#include "utils/tests_helper.h"


static constexpr std::string_view kRealKey( TEST_RES_DIR "/chitin.key" );

TEST( KeyFileTest, KeyIsUnreadableTest )
{
    const auto key = KeyFile::open( "nonexistent.key" );
    ASSERT_TRUE( not key && key.error().type() == IEErrorType::Unreadable );
}

TEST( KeyFileTest, KeyIsMalformedVersion )
{
    const TempCreator temp( "invalid_version.key", "KEY ", "Invl" );
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( not key && key.error().type() == IEErrorType::Malformed );
}

TEST( KeyFileTest, KeyIsMalformedSignature )
{
    const TempCreator temp( "invalid_signature.key", "XXXX", "V1  " );
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( not key && key.error().type() == IEErrorType::Malformed );
}

TEST( KeyFileTest, RealKeyIsReadableAndValid )
{
    const auto key = KeyFile::open( kRealKey );
    ASSERT_TRUE( key.has_value() );
}

TEST( KeyFileTest, KeyIsReadableAndValid )
{
    const TempCreator temp( "valid_key.key", "KEY ", "V1  " );
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( key.has_value() );
}
