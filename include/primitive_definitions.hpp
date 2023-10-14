/// @file primitive_definitions.hpp
/// @brief Primitive type declarations like scalar indices and so on.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED
#define OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>


/// Root namespace of the OGxx library.
namespace ogxx
{

  /////////////////////////////////////////////////////////////////////////////
  // Types

  /// @brief Linear sequence size.
  using Scalar_size = std::ptrdiff_t;

  /// @brief Linear random-access sequence index.
  using Scalar_index = std::ptrdiff_t;

  /// @brief 32-bit integer for weights and lengths.
  using Int = std::int32_t;

  /// @brief Default floating point number type used for weights and lengths.
  using Float = double;


  /////////////////////////////////////////////////////////////////////////////
  // Constants

  /// @brief Infinity float value for convenience.
  constexpr Float infinity = std::numeric_limits<Float>::infinity();


  /////////////////////////////////////////////////////////////////////////////
  // Functions

  /// @brief Check if a value is within a segment with the specified bounds
  /// @param value the value to check
  /// @param lower the lower bound for the value
  /// @param upper the upper bound for the value
  /// @return true if lower <= value and value <= upper
  [[nodiscard]] constexpr auto is_within(auto const& value, auto const& lower, auto const& upper)
    noexcept(noexcept(lower <= value && value <= upper))
    -> bool
  {
    return lower <= value && value <= upper;
  }

  // max

  // min

  // clamp

}

#endif//OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED
