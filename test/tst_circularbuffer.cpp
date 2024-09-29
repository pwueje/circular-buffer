/*********************************************************************
 * @file   tst_circularbuffer.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-04
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#include <gtest/gtest.h>
#include <pjexx/circularbuffer.h>

namespace pjexx::circularbuffer::test
{
class CircularBufferTest : public ::testing::Test
{
  public:
    static constexpr std::size_t BUFFER_SIZE = 5;
};

TEST_F(CircularBufferTest, TestConstruction)
{
    CircularBuffer<int, BUFFER_SIZE> uut;
    EXPECT_EQ(uut.max_size(), BUFFER_SIZE);
    EXPECT_EQ(uut.capacity(), BUFFER_SIZE);
    EXPECT_EQ(uut.size(), 0);
    EXPECT_TRUE(uut.empty());
}

TEST_F(CircularBufferTest, TestConstructionWithValues)
{
    CircularBuffer<int, BUFFER_SIZE> uut {0, 1, 2};

    EXPECT_EQ(uut.max_size(), BUFFER_SIZE);
    EXPECT_EQ(uut.capacity(), BUFFER_SIZE);
    EXPECT_EQ(uut.size(), 3);
    EXPECT_FALSE(uut.empty());
}

TEST_F(CircularBufferTest, TestEmplaceBackOnce)
{
    constexpr int value = 5;
    CircularBuffer<int, BUFFER_SIZE> uut;
    auto ref = uut.emplace(value);
    EXPECT_EQ(ref, value);
    EXPECT_EQ(uut.size(), 1);
    EXPECT_FALSE(uut.empty());
}

TEST_F(CircularBufferTest, TestEmplaceBackMultipleTimes)
{
    constexpr int value = 5;
    CircularBuffer<int, BUFFER_SIZE> uut;
    uut.emplace(value);
    auto ref = uut.emplace(value + 1);

    EXPECT_EQ(ref, value + 1);
    EXPECT_EQ(uut.size(), 2);
    EXPECT_FALSE(uut.empty());
}

TEST_F(CircularBufferTest, TestEmplaceBackMoreThanCapacity)
{
    constexpr int value = 5;
    CircularBuffer<int, BUFFER_SIZE> uut;

    int actual = -1;
    for (uint i = 0; i <= BUFFER_SIZE; i++)
    {
        actual = uut.emplace(value + i);
    }

    EXPECT_EQ(actual, value + BUFFER_SIZE);
    EXPECT_EQ(uut.size(), BUFFER_SIZE);
    EXPECT_EQ(uut.max_size(), BUFFER_SIZE);
    EXPECT_EQ(uut.capacity(), BUFFER_SIZE);
    EXPECT_FALSE(uut.empty());
}

TEST_F(CircularBufferTest, TestData)
{
    constexpr int value = 611;
    CircularBuffer<int, BUFFER_SIZE> uut;
    auto &actual  = uut.emplace(value);
    auto *dataPtr = uut.data();
    EXPECT_NE(dataPtr, nullptr);
    EXPECT_EQ(*dataPtr, value);
    EXPECT_EQ(&actual, dataPtr);
}

TEST_F(CircularBufferTest, TestDataConst)
{
    constexpr int value = 611;
    CircularBuffer<int, BUFFER_SIZE> uut;
    auto &actual = uut.emplace(value);

    auto validate = [&actual, &value](const auto &uut)
    {
        auto *dataPtr = uut.data();
        EXPECT_NE(dataPtr, nullptr);
        EXPECT_EQ(*dataPtr, value);
        EXPECT_EQ(&actual, dataPtr);
    };

    validate(uut);
}

TEST_F(CircularBufferTest, TestDataAccess)
{
    constexpr int value = 41;
    CircularBuffer<int, BUFFER_SIZE> uut;

    for (int i = 0; i < 3; i++)
    {
        uut.emplace(value + i);
    }

    auto validate = [&value](const auto &uut)
    {
        for (uint i = 0; i < 3; i++)
        {
            EXPECT_EQ(uut[i], value + i);
        }
    };

    validate(uut);
}

TEST_F(CircularBufferTest, TestDataAccessConst)
{
    constexpr int value = 41;
    CircularBuffer<int, BUFFER_SIZE> uut;

    for (int i = 0; i < 3; i++)
    {
        uut.emplace(value + i);
    }

    for (uint i = 0; i < 3; i++)
    {
        EXPECT_EQ(uut[i], value + i);
    }
}

TEST_F(CircularBufferTest, TestPushBackCopy)
{
    constexpr std::string_view value = "41";
    CircularBuffer<std::string, BUFFER_SIZE> uut;
    uut.push_back(value);
}

TEST_F(CircularBufferTest, TestPushBackMove)
{
    constexpr std::string_view value = "41";
    CircularBuffer<std::string, BUFFER_SIZE> uut;
    uut.push_back(std::string {value});
}

TEST_F(CircularBufferTest, TestPushBackMoreOftenThanBufferSize)
{
    constexpr int value = 5;
    CircularBuffer<int, BUFFER_SIZE> uut;

    for (uint i = 0; i <= BUFFER_SIZE; i++)
    {
        uut.push_back(value + i);
    }

    EXPECT_EQ(uut.size(), BUFFER_SIZE);
    EXPECT_EQ(uut.max_size(), BUFFER_SIZE);
    EXPECT_EQ(uut.capacity(), BUFFER_SIZE);
    EXPECT_FALSE(uut.empty());
}

TEST_F(CircularBufferTest, TestIterate)
{
    CircularBuffer<int, BUFFER_SIZE> uut {0, 1, 2};

    int expected = 0;
    ASSERT_EQ(uut.size(), 3);
    int iterated = 0;

    for (auto value : uut)
    {
        ++iterated;
        EXPECT_EQ(value, expected++);
    }

    EXPECT_EQ(iterated, 3);
}

TEST_F(CircularBufferTest, TestIterateConst)
{
    CircularBuffer<int, BUFFER_SIZE> uut {0, 1, 2};

    ASSERT_EQ(uut.size(), 3);

    auto validate = [](const auto &uut)
    {
        int expected = 0;
        int iterated = 0;

        for (auto value : uut)
        {
            ++iterated;
            EXPECT_EQ(value, expected++);
        }

        EXPECT_EQ(iterated, 3);
    };

    validate(uut);
}
}  // namespace pjexx::circularbuffer::test
