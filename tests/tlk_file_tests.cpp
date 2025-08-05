#include <gtest/gtest.h>
#include "../src/tlk_file.h"
#include <fstream>
#include <filesystem>
#include <optional>
#include <iostream>
#include "../src/xref.h"

TEST( TlkFileTest, TlkIsUnreadableTest ) {
    EXPECT_TRUE( TlkFile( "nonexistent.tlk" ).get_state() ==
        TlkFileState::Unreadable);
}

TEST( TlkFileTest, TlkIsMalformedVersion ) {
    std::ofstream ofs( "invalid_signature.tlk", std::ios::binary);
    ofs.write("TLK ", 4); // Valid signature
    ofs.write( "Invl", 4 ); // Invalid version
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_signature.tlk" ).get_state() ==
        TlkFileState::ReadableButMalformed );
    std::filesystem::remove( "invalid_signature.tlk" );
}

TEST( TlkFileTest, TlkIsMalformedSignature ) {
    std::ofstream ofs( "invalid_signature.tlk", std::ios::binary );
    ofs.write( "XXXX", 4 ); // Invalid signature
    ofs.close();
    EXPECT_TRUE( TlkFile( "invalid_signature.tlk" ).get_state() ==
        TlkFileState::ReadableButMalformed );
    std::filesystem::remove( "invalid_signature.tlk" );
}

TEST( TlkFileTest, TlkHasExpectedTextAtIndexOne ) {
    TlkFile tlk( "dialog.tlk" );
    EXPECT_EQ( tlk.get_state(), TlkFileState::ReadableAndValid);
    const auto result = tlk.at_index( 1 );
    EXPECT_TRUE( result.has_value() );
    EXPECT_TRUE( *result == "No, I'm sorry, none of them sound familiar." );
}
