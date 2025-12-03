#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string_view>

#include "../src/backend/ie_files.h"
#include "../src/backend/key_file.h"

#include "utils/tests_helper.h"

static constexpr std::string_view kRealKey("../tests/res/chitin.key");

TEST( KeyFileTest, KeyIsUnreadableTest )
{
    const auto key = KeyFile::open( "nonexistent.key" );
    ASSERT_TRUE( !key && key.error().error_type == IEErrorType::Unreadable );
}

TEST(KeyFileTest, KeyIsMalformedVersion)
{
    const TempCreator temp("invalid_version.key", "KEY ", "Invl");
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( !key && key.error().error_type == IEErrorType::Malformed );
}

TEST( KeyFileTest, KeyIsMalformedSignature )
{
    const TempCreator temp( "invalid_signature.key", "XXXX", "V1  " );
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( !key && key.error().error_type == IEErrorType::Malformed );
}

TEST( KeyFileTest, RealKeyIsReadableAndValid )
{
    ASSERT_TRUE( KeyFile::open(kRealKey).has_value() );
}

TEST( KeyFileTest, KeyIsReadableAndValid )
{
    const TempCreator temp( "valid_key.key", "KEY ", "V1  " );
    const auto key = KeyFile::open( temp.name );
    ASSERT_TRUE( key.has_value() );
}