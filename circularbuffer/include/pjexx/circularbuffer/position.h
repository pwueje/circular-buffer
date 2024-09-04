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

#include <compare>
#include <concepts>
#include <cstddef>

namespace pjexx::circularbuffer::detail
{
template <std::size_t Capacity>
class Position
{
    using self_type = Position<Capacity>;

  public:
    using underlying_type = std::size_t;
    constexpr Position() : _value {0} {}

    constexpr explicit Position(std::integral auto value) : _value {static_cast<underlying_type>(value)} {}

    constexpr operator underlying_type() const { return _value; }

    constexpr self_type& operator++()
    {
        ++_value;

        if (_value == Capacity)
        {
            _value = 0;
        }

        return *this;
    }

    constexpr self_type operator++(int)
    {
        self_type tmp = *this;
        operator++();
        return tmp;
    }

    constexpr self_type& operator--()
    {
        if (_value == 0)
        {
            _value = Capacity - 1;
        }
        else
        {
            --_value;
        }

        return *this;
    }

    constexpr self_type operator--(int)
    {
        self_type tmp = *this;
        operator--();
        return tmp;
    }

    friend constexpr bool operator==(const self_type& lhs, const self_type& rhs) { return lhs._value == rhs._value; }

    friend constexpr std::strong_ordering operator<=>(const self_type& lhs, const self_type& rhs)
    {
        return lhs._value <=> rhs._value;
    }

  private:
    std::size_t _value;
};
}  // namespace pjexx::circularbuffer::detail

#endif
