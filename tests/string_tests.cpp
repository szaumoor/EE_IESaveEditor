#include <gtest/gtest.h>

#include "../src/backend/utils/helper_structs.h"

TEST(StringTests, EmptyCharArrayConvertsToEmptyString)
{
    constexpr CharArray<8> array{};
    const auto str = array.to_string();
    ASSERT_TRUE(str.empty());
}

TEST(StringTests, CharArrayFullOfNullsConvertsToEmptyString)
{
    constexpr CharArray<8> array{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    const auto str = array.to_string();
    ASSERT_TRUE(str.empty());
}

TEST(StringTests, CharArrayConvertsToCorrectString)
{
    constexpr CharArray<8> array{'H', 'e', 'l', 'l', 'o', '\0', '\0', '\0'};
    const auto str = array.to_string();
    ASSERT_TRUE(str == "Hello");
}