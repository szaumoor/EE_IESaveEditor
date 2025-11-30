#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../src/backend/ie_files.h"
#include "../src/backend/key_file.h"

#include "utils/tests_helper.h"

constexpr auto real_path = "../tests/res/chitin.key";

TEST( KeyFileTest, KeyIsUnreadableTest )
{
    ASSERT_TRUE( KeyFile( "nonexistent.key" ).unreadable() );
}

TEST( KeyFileTest, KeyIsMalformedVersion )
{
    const auto temp = TempCreator( "invalid_version.key", "KEY ", "Invl" );
    ASSERT_TRUE( KeyFile( temp.name ).malformed() );
}

TEST( KeyFileTest, KeyIsMalformedSignature )
{
    const auto temp = TempCreator( "invalid_signature.key", "XXXX", "V1  " );
    ASSERT_TRUE( KeyFile( temp.name ).malformed() );
}

TEST( KeyFileTest, RealKeyIsReadableAndValid )
{
    ASSERT_TRUE( KeyFile( real_path ).good() );
}

TEST( KeyFileTest, KeyIsReadableAndValid )
{
    const auto temp = TempCreator( "valid_key.key", "KEY ", "V1  " );
    ASSERT_TRUE( KeyFile( temp.name ).good() );
}