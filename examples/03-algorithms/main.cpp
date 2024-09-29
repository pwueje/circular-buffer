/*********************************************************************
 * @file   main.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-29
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#include <format>
#include <iostream>
#include <numeric>

#include "pjexx/circularbuffer.h"

int main()
{
    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    pjexx::circularbuffer::CircularBuffer<int, 2U> buff {6, 11, 42};
    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    std::cout << "Sum up ";

    for (auto item : buff)
    {
        std::cout << std::format("{} ", item);
    }

    std::cout << std::format("result in {}\n", std::accumulate(buff.begin(), buff.end(), 0));

    return EXIT_SUCCESS;
}
