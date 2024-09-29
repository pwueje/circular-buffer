/*********************************************************************
 * @file   iterators.h
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-29
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#pragma once
#ifndef INCLUDE_PJEXX_CIRCULARBUFFER_iterators_H
#define INCLUDE_PJEXX_CIRCULARBUFFER_iterators_H

#include <iterator>
#include <type_traits>

#include "position.h"

namespace pjexx::circularbuffer::detail
{
template <class T>
using PlainType = T;

template <class T>
using Const = const T;

template <class T, std::size_t Capacity, template <class> typename TypeModifier = PlainType>
class CircularBufferIterator
{
    using self_type = CircularBufferIterator<T, Capacity, TypeModifier>;
    using pos_type  = Position<Capacity>;
    using size_type = std::size_t;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type      = T;
    using reference       = TypeModifier<value_type>&;
    using pointer         = TypeModifier<value_type>*;

    constexpr CircularBufferIterator(pointer ptr, pos_type position, size_type numberOfElements)
        : _ptr {ptr}, _currentPosition {position}, _numberOfElements {numberOfElements}, _increments {0}
    {
    }

    constexpr CircularBufferIterator(pointer ptr, pos_type position, size_type numberOfElements, size_type increments)
        : _ptr {ptr}, _currentPosition {position}, _numberOfElements {numberOfElements}, _increments {increments}
    {
    }

    constexpr reference operator*() { return *effectivePointer(); }
    constexpr pointer operator->() { return effectivePointer(); }

    constexpr self_type operator++(int)
    {
        self_type tmp = *this;
        operator++();
        return tmp;
    }

    constexpr self_type& operator++()
    {
        ++_currentPosition;
        ++_increments;
        return *this;
    }

    constexpr friend bool operator==(const self_type& lhs, const self_type& rhs)
    {
        return lhs._increments == rhs._increments && lhs._numberOfElements == rhs._numberOfElements &&
               lhs.effectivePointer() == rhs.effectivePointer();
    }

  private:
    pointer _ptr;
    pos_type _currentPosition;
    const size_type _numberOfElements;
    size_type _increments;

    constexpr pointer effectivePointer() const
    {
        if (_increments < _numberOfElements)
        {
            return (_ptr + static_cast<size_type>(_currentPosition));
        }
        else
        {
            return (_ptr + Capacity + 1);
        }
    }
};
}  // namespace pjexx::circularbuffer::detail

#endif
