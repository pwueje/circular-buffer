/*********************************************************************
 * @file   main.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-03
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#include <iostream>
#include <format>

#include "pjexx/circularbuffer.h"

int main()
{
    pjexx::circularbuffer::CircularBuffer<int, 2U> buff;

    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    buff.emplace(6);
    buff.emplace(11);
    buff.emplace(42);
    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    std::cout << std::format("buff[0]: {}\n", buff[0]);
    std::cout << std::format("buff[1]: {}\n", buff[1]);

    return EXIT_SUCCESS;
}
