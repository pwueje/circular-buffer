/*********************************************************************
 * @file   tst_position.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-04
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#include <gtest/gtest.h>
#include <pjexx/circularbuffer/position.h>

namespace pjexx::circularbuffer::detail::test
{
class PositionTest : public ::testing::Test
{
};

TEST_F(PositionTest, TestConstruction) { Position<42> uut; }
TEST_F(PositionTest, TestConstructionWithValue) { Position<42> uut {7}; }

TEST_F(PositionTest, TestEqualityWithUnderlyingType)
{
    Position<42> uut {7};
    EXPECT_EQ(uut, 7);
}

TEST_F(PositionTest, TestEquality)
{
    Position<42> uut1 {7};
    Position<42> uut2 {7};
    EXPECT_EQ(uut1, uut2);
}

TEST_F(PositionTest, TestLess)
{
    Position<42> uut1 {7};
    Position<42> uut2 {21};
    EXPECT_LT(uut1, uut2);
}

TEST_F(PositionTest, TestGreater)
{
    Position<42> uut1 {21};
    Position<42> uut2 {7};
    EXPECT_GT(uut1, uut2);
}

TEST_F(PositionTest, TestPreIncrementWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(++uut, 8);
    EXPECT_EQ(++uut, 9);
}

TEST_F(PositionTest, TestPostIncrementWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut++, 7);
    EXPECT_EQ(uut++, 8);
    EXPECT_EQ(uut++, 9);
}

TEST_F(PositionTest, TestPreDecrementWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(--uut, 6);
    EXPECT_EQ(--uut, 5);
}

TEST_F(PositionTest, TestPostDecrementWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut--, 7);
    EXPECT_EQ(uut--, 6);
    EXPECT_EQ(uut--, 5);
}

TEST_F(PositionTest, TestPreIncrementWithWrap)
{
    Position<9> uut {7};
    EXPECT_EQ(++uut, 8);
    EXPECT_EQ(++uut, 0);
}

TEST_F(PositionTest, TestPostIncrementWithWrap)
{
    Position<9> uut {7};
    EXPECT_EQ(uut++, 7);
    EXPECT_EQ(uut++, 8);
    EXPECT_EQ(uut++, 0);
}

TEST_F(PositionTest, TestPreDecrementWithWrap)
{
    Position<42> uut {1};
    EXPECT_EQ(--uut, 0);
    EXPECT_EQ(--uut, 41);
}

TEST_F(PositionTest, TestPostDecrementWithWrap)
{
    Position<42> uut {1};
    EXPECT_EQ(uut--, 1);
    EXPECT_EQ(uut--, 0);
    EXPECT_EQ(uut--, 41);
}

TEST_F(PositionTest, TestAddValueWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut + 14, 21);
}

TEST_F(PositionTest, TestAddValueAssignmentWithoutWrap)
{
    Position<42> uut {7};
    uut += 14;
    EXPECT_EQ(uut, 21);
}

TEST_F(PositionTest, TestAddValueWithWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut + 35, 0);
}

TEST_F(PositionTest, TestAddValueAssignmentWithWrap)
{
    Position<42> uut {7};
    uut += 35;
    EXPECT_EQ(uut, 0);
}


TEST_F(PositionTest, TestSubtractValueWithoutWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut - 5, 2);
}

TEST_F(PositionTest, TestSubtractValueAssignmentWithoutWrap)
{
    Position<42> uut {7};
    uut -= 5;
    EXPECT_EQ(uut, 2);
}

TEST_F(PositionTest, TestSubtractValueWithWrap)
{
    Position<42> uut {7};
    EXPECT_EQ(uut - 8, 41);
}

TEST_F(PositionTest, TestSubtractValueAssignmentWithWrap)
{
    Position<42> uut {7};
    uut -= 8;
    EXPECT_EQ(uut, 41);
}
}  // namespace pjexx::circularbuffer::detail::test
