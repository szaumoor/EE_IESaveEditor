#include <gtest/gtest.h>

#include <array>

#include "../src/backend/tlk_file.hpp"
#include "../src/frontend/helpers/qt_strings.hpp"

namespace
{
    constexpr std::string_view kRealTlk(TEST_RES_DIR "/dialog.tlk");
}

TEST(QtStringTests, EmptyStdStringConvertsToEmptyQString)
{
    const std::string input;
    EXPECT_TRUE(str::from(input).isEmpty());
}

TEST(QtStringTests, StdStringConvertsAsciiText)
{
    const std::string input = "Baldur's Gate";
    EXPECT_EQ(str::from(input), QStringLiteral("Baldur's Gate"));
}

TEST(QtStringTests, StdStringConvertsUtf8Text)
{
    const std::string input = "Espa\xc3\xb1ol";
    EXPECT_EQ(str::from(input), QStringLiteral("Espa\u00f1ol"));
}

TEST(QtStringTests, StdStringPreservesEmbeddedNulls)
{
    const std::string input{"A\0B", 3};
    const QString result = str::from(input);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result.at(0), QChar('A'));
    EXPECT_TRUE(result.at(1).isNull());
    EXPECT_EQ(result.at(2), QChar('B'));
}

TEST(QtStringTests, NullCharPointerConvertsToNullQString)
{
    constexpr const char* input = nullptr;
    const QString result = str::from(input);

    EXPECT_TRUE(result.isNull());
}

TEST(QtStringTests, CharPointerConvertsUtf8Text)
{
    constexpr auto input = "caf\xc3\xa9";

    EXPECT_EQ(str::from(input), QStringLiteral("caf\u00e9"));
}

TEST(QtStringTests, CharPointerStopsAtFirstNull)
{
    constexpr char input[] = {'A', '\0', 'B', '\0'};

    EXPECT_EQ(str::from(input), QStringLiteral("A"));
}

TEST(QtStringTests, EmptyStringViewConvertsToEmptyQString)
{
    constexpr std::string_view input;

    EXPECT_TRUE(str::from(input).isEmpty());
}

TEST(QtStringTests, StringViewDoesNotReadPastItsBounds)
{
    constexpr std::array storage{'V', 'i', 'e', 'w', 'X', 'Y', 'Z'};
    const std::string_view input(storage.data(), 4);

    EXPECT_EQ(str::from(input), QStringLiteral("View"));
}

TEST(QtStringTests, StringViewPreservesEmbeddedNulls)
{
    constexpr std::array storage{'A', '\0', 'B'};
    const std::string_view input(storage.data(), storage.size());
    const QString result = str::from(input);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result.at(0), QChar('A'));
    EXPECT_TRUE(result.at(1).isNull());
    EXPECT_EQ(result.at(2), QChar('B'));
}

TEST(QtStringTests, StringViewConvertsNonNullTerminatedUtf8Text)
{
    constexpr std::array storage{
        'c', 'a', 'f', static_cast<char>(0xc3), static_cast<char>(0xa9)
    };
    const std::string_view input(storage.data(), storage.size());

    EXPECT_EQ(str::from(input), QStringLiteral("caf\u00e9"));
}

TEST(QtStringTests, IEStringViewConvertsTextFromTlkFile)
{
    const auto tlk = TlkFile::open(kRealTlk);
    ASSERT_TRUE(tlk.has_value());

    const auto input = tlk->at(1);
    ASSERT_TRUE(input.has_value());
    EXPECT_EQ(str::from(*input),
    QStringLiteral("No, I'm sorry, none of them sound familiar."));
}

TEST(QtStringTests, EmptyCharArrayConvertsToEmptyQString)
{
    constexpr CharArray<8> input{};
    EXPECT_TRUE(str::from(input).isEmpty());
}

TEST(QtStringTests, NullPaddedCharArrayConvertsUntilFirstNull)
{
    constexpr CharArray<8> input{'M', 'i', 'n', 's', 'c', '\0', '\0', '\0'};
    EXPECT_EQ(str::from(input), QStringLiteral("Minsc"));
}

TEST(QtStringTests, CharArrayIgnoresBytesAfterFirstNull)
{
    constexpr CharArray<8> input{'A', 'B', '\0', 'X', 'Y', 'Z', '1', '2'};

    EXPECT_EQ(str::from(input), QStringLiteral("AB"));
}

TEST(QtStringTests, FullCharArrayDoesNotReadPastItsBounds)
{
    constexpr CharArray<8> input{'F', 'U', 'L', 'L', 'T', 'E', 'X', 'T'};

    EXPECT_EQ(str::from(input), QStringLiteral("FULLTEXT"));
}

TEST(QtStringTests, FullCharArrayConvertsUtf8Text)
{
    constexpr CharArray<2> input{
        static_cast<char>(0xc3), static_cast<char>(0xa9)
    };

    EXPECT_EQ(str::from(input), QStringLiteral("\u00e9"));
}

TEST(QtStringTests, IEErrorConvertsDefaultMessage)
{
    const IEError input(IEErrorType::Malformed);

    EXPECT_EQ(str::from(input), QStringLiteral("Malformed file."));
}

TEST(QtStringTests, IEErrorConvertsCustomMessage)
{
    const IEError input(IEErrorType::Unreadable, "Custom read error");

    EXPECT_EQ(str::from(input), QStringLiteral("Custom read error"));
}
