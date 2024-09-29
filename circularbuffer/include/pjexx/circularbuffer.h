/*********************************************************************
 * @file   circularbuffer.h
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-03
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#pragma once
#ifndef INCLUDE_PJEXX_CIRCULARBUFFER_H
#define INCLUDE_PJEXX_CIRCULARBUFFER_H

#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>

#include "circularbuffer/position.h"
#include "concepts.h"

namespace pjexx::circularbuffer
{
template <class T, std::size_t Capacity, class Allocator = std::allocator<T>>
class CircularBuffer
{
  public:
    using value_type      = T;
    using allocator_type  = Allocator;
    using allocator_trait = std::allocator_traits<allocator_type>;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename allocator_trait::pointer;
    using const_pointer   = typename allocator_trait::const_pointer;

    constexpr CircularBuffer() : _data {allocator_trait::allocate(_allocator, Capacity)} {}

    constexpr explicit CircularBuffer(std::initializer_list<value_type> values, const Allocator& allocator = Allocator())
        : _allocator(allocator), _data {allocator_trait::allocate(_allocator, Capacity)}
    {
        for (auto value : values)
        {
            push_back(value);
        }
    }

    constexpr ~CircularBuffer() noexcept { allocator_trait::deallocate(_allocator, _data, Capacity); }

    constexpr reference operator[](size_type pos) { return *(_data + static_cast<size_type>(_currentStart + pos)); }
    constexpr const_reference operator[](size_type pos) const
    {
        return *(_data + static_cast<size_type>(_currentStart + pos));
    }

    template <class Arg>
    constexpr void push_back(Arg&& value)
    {
        pointer currentPtr = (_data + static_cast<size_type>(_currentEnd++));
        allocator_trait::construct(_allocator, currentPtr, std::forward<Arg>(value));

        incrementElementCount();
    }

    template <class... Args>
    constexpr reference emplace(Args&&... args)
    {
        pointer currentPtr = (_data + static_cast<size_type>(_currentEnd++));
        allocator_trait::construct(_allocator, currentPtr, std::forward<Args>(args)...);

        incrementElementCount();

        return *currentPtr;
    }

    constexpr size_type capacity() const { return Capacity; }
    constexpr size_type max_size() const { return Capacity; }
    constexpr size_type size() const { return _numberOfElements; }
    constexpr bool empty() const { return _numberOfElements == 0; }

    constexpr pointer data() { return _data; }
    constexpr const_pointer data() const { return _data; }

  private:
    allocator_type _allocator;
    pointer _data;
    size_type _numberOfElements = 0;

    detail::Position<Capacity> _currentStart;
    detail::Position<Capacity> _currentEnd;

    constexpr void incrementElementCount()
    {
        if (_numberOfElements == Capacity)
        {
            ++_currentStart;
        }
        else
        {
            ++_numberOfElements;
        }
    }
};
}  // namespace pjexx::circularbuffer
#endif
