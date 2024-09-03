/*********************************************************************
 * @file   concepts.h
 * @brief
 *
 * @author Philipp Jeske
 * @date   2024-09-03
 *********************************************************************/
/* SPDX-License-Identifier: MIT */

#pragma once
#ifndef INCLUDE_PJEXX_CONCEPTS_H
#define INCLUDE_PJEXX_CONCEPTS_H

#include <concepts>

namespace pjexx::concepts
{
template <typename T>
concept Numeric = std::integral<T> && !std::same_as<bool, T>;

template <typename T>
concept UnsignedNumeric = std::unsigned_integral<T> && !std::same_as<bool, T>;

template <typename T>
concept SignedNumeric = std::signed_integral<T> && !std::same_as<bool, T>;
}  // namespace pjexx::concepts

#endif
