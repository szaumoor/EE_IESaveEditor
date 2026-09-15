#include <gtest/gtest.h>

#include "../src/backend/utils/helper_structs.hpp"

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

TEST(StringTests, CharArrayConversionStopsAtFirstNull)
{
    constexpr CharArray<8> array{'A', 'B', '\0', 'X', 'Y', 'Z', '1', '2'};

    EXPECT_EQ(array.to_string(), "AB");
}

TEST(StringTests, FromStringAcceptsTextAtExactCapacity)
{
    const auto array = CharArray<5>::from_string("DYNHE");

    ASSERT_TRUE(array.has_value());
    EXPECT_EQ(array->to_string(), "DYNHE");
}

TEST(StringTests, FromStringZeroFillsUnusedCharacters)
{
    const auto array = CharArray<5>::from_string("Imo");

    ASSERT_TRUE(array.has_value());
    EXPECT_EQ(array->value[0], 'I');
    EXPECT_EQ(array->value[1], 'm');
    EXPECT_EQ(array->value[2], 'o');
    EXPECT_EQ(array->value[3], '\0');
    EXPECT_EQ(array->value[4], '\0');
}

TEST(StringTests, FromStringRejectsTextLargerThanCapacity)
{
    const auto array = CharArray<4>::from_string("Imoen");

    EXPECT_FALSE(array.has_value());
}

TEST(StringTests, AssignStringReplacesExistingValue)
{
    CharArray<8> array{'J', 'a', 'h', 'e', 'i', 'r', 'a', '\0'};

    ASSERT_TRUE(array.assign_string("Viconia"));
    EXPECT_EQ(array.to_string(), "Viconia");
    EXPECT_EQ(array.value[7], '\0');
}

TEST(StringTests, AssignStringClearsExistingValue)
{
    CharArray<8> array{'J', 'a', 'h', 'e', 'i', 'r', 'a', '\0'};

    ASSERT_TRUE(array.assign_string(""));
    EXPECT_TRUE(array.to_string().empty());
    EXPECT_EQ(array.value[0], '\0');
}

TEST(StringTests, FailedAssignStringLeavesExistingValueUnchanged)
{
    CharArray<4> array{'K', 'e', 'e', 'p'};

    EXPECT_FALSE(array.assign_string("Too long"));
    EXPECT_EQ(array.to_string(), "Keep");
}

TEST(StringTests, ResrefConvertsUsingItsCharArrayValue)
{
    constexpr Resref resref{CharArray<8>{'S', 'W', '1', 'F', 'I', 'R', 'E', '\0'}};

    EXPECT_EQ(resref.to_string(), "SW1FIRE");
}
