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
#include <string>

#include "pjexx/circularbuffer.h"

namespace
{
struct MyData
{
    int number;
    std::string str;
};
}  // namespace

template <>
struct std::formatter<MyData> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const MyData& item, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", item.number, item.str);
    }
};

int main()
{
    pjexx::circularbuffer::CircularBuffer<MyData, 2U> buff;

    // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
    buff.emplace(6,"Lorem");
    buff.emplace(11,"Ipsum");
    buff.emplace(42, "Dolor");
    // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

    std::cout << std::format("buff[0]: {}\n", buff[0]);
    std::cout << std::format("buff[1]: {}\n", buff[1]);

    return EXIT_SUCCESS;
}
