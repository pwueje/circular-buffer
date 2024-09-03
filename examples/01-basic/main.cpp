/*********************************************************************
 * @file   main.cpp
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-03
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#include <iostream>

#include "pjexx/circularbuffer.h"

int main()
{
    pjexx::circularbuffer::CircularBuffer<int, 2u> buff;

    buff.emplace(6);
    buff.emplace(11);

    std::cout << "buff[0]: " << buff[0] << std::endl;
    std::cout << "buff[1]: " << buff[1] << std::endl;

    return EXIT_SUCCESS;
}
