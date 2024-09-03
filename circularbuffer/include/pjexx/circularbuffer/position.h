/*********************************************************************
 * @file   position.h
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-03
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#pragma once
#ifndef INCLUDE_PJEXX_CIRCULARBUFFER_POSITION_H
#define INCLUDE_PJEXX_CIRCULARBUFFER_POSITION_H

#include <concepts>
#include <cstddef>

namespace pjexx::circularbuffer::detail
{
template <std::size_t Capacity>
class Position
{
    using self_type = Position<Capacity>;

  public:
    constexpr Position() : _value {0} {}

    constexpr explicit Position(std::integral auto value) : _value {value} {}

    constexpr operator std::size_t() const { return _value; }

    constexpr self_type operator++(int)
    {
        self_type tmp = *this;
        ++_value;
        return tmp;
    }

  private:
    std::size_t _value;
};
}  // namespace pjexx::circularbuffer::detail

#endif
