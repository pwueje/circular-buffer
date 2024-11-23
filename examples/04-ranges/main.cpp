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
#include <ranges>

#include "pjexx/circularbuffer.h"

int main()
{
    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    pjexx::circularbuffer::CircularBuffer<int, 2U> buff {6, 11, 42};
    static_assert(std::ranges::forward_range<decltype(buff)>);
    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    std::cout << "Origin ";

    for (auto item : buff)
    {
        std::cout << std::format("{} ", item);
    }

    std::cout << "\nIs even ";

    auto isEven = [](const auto &value) { return value % 2 == 0; };

    for (auto item : (buff | std::views::transform(isEven)))
    {
        std::cout << std::format("{} ", item);
    }

    std::cout << "\n";

    return EXIT_SUCCESS;
}
