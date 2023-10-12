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

  /// @brief Linear sequence size.
  using Scalar_size = std::ptrdiff_t;

  /// @brief Linear random-access sequence index.
  using Scalar_index = std::ptrdiff_t;

  /// @brief 32-bit integer for weights and lengths.
  using Int = std::int32_t;

  /// @brief Default floating point number type used for weights and lengths.
  using Float = double;

  /// @brief Infinity float value for convenience.
  constexpr Float infinity = std::numeric_limits<Float>::infinity();

}

#endif//OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED
