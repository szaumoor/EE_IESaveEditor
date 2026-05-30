#include <gtest/gtest.h>

#include <string_view>

#include "../src/backend/biff_file.h"
// #include "../src/backend/tlk_file.h"
#include "../src/backend/utils/errors.h"

#include "utils/tests_helper.h"

static constexpr std::string_view kRealBiff(TEST_RES_DIR "/Spells.bif");
static constexpr std::string_view kRealBiffWithTilesets(TEST_RES_DIR "/25ArMisc.bif");

// static constexpr std::string_view kRealTlk( TEST_RES_DIR "/dialog.tlk" );
// static const auto real_tlk = TlkFile::open( kRealTlk );

TEST( BiffFileTests, BiffIsUnreadableTest )
{
    const auto biff = BiffFile::open("nonexistent.biff");
    ASSERT_TRUE( not biff && biff.error().type() == IEErrorType::Unreadable );
}

TEST( BiffFileTests, BiffIsMalformedVersion )
{
    const ZS::TempCreator temp("invalid_version.biff", "BIFF", "Invl");
    const auto biff = BiffFile::open(temp.m_name);
    ASSERT_TRUE( not biff && biff.error().type() == IEErrorType::Malformed );
}

TEST( BiffFileTests, BiffIsMalformedSig )
{
    const ZS::TempCreator temp("invalid_version.biff", "BUFF", "V1  ");
    const auto biff = BiffFile::open(temp.m_name);
    ASSERT_TRUE( not biff && biff.error().type() == IEErrorType::Malformed );
}

TEST( BiffFileTests, RealBiffIsReadableAndValid )
{
    const auto biff = BiffFile::open( kRealBiff );
    ASSERT_TRUE( biff.has_value() );
}

TEST( BiffFileTests, RealBiffWithTilesetsIsReadableAndValid )
{
    const auto biff = BiffFile::open( kRealBiffWithTilesets );
    ASSERT_TRUE( biff.has_value() );
}
