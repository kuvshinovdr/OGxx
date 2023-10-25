/// @file primitive_definitions.hpp
/// @brief Primitive type declarations like scalar indices and so on.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED
#define OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <memory>
#include <utility>


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

  /// @brief Invalid position in a container with zero-based indexing.
  constexpr Scalar_index npos = -1;

  /// @brief Infinity float value for convenience.
  constexpr Float infinity = std::numeric_limits<Float>::infinity();


  /////////////////////////////////////////////////////////////////////////////
  // Functions

  /// @brief Check if a value is within a segment with the specified bounds, uses operator<=
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


  /// @brief Clamp a value into [lower, upper] segment, uses operator<
  /// @tparam Val value type
  /// @tparam Lo lower bound type
  /// @tparam Up upper bound type
  /// @param value the value to be clamped
  /// @param lower the lower bound
  /// @param upper the upper bound
  /// @return lower if value < lower, upper if upper < value, value if it is within [lower, upper]
  template <typename Val, typename Lo, typename Up>
  [[nodiscard]] constexpr auto clamp(Val&& value, Lo&& lower, Up&& upper)
    -> std::common_type_t<Val, Lo, Up>
  {
    if (value < lower)
      return std::forward<Lo>(lower);
    if (upper < value)
      return std::forward<Up>(upper);
    return std::forward<Val>(value);
  }


  /// @brief Forward the maximal value between first and second (by reference if it is passed by reference, by value otherwise).
  template <typename First, typename Second>
  [[nodiscard]] constexpr decltype(auto) max(First&& first, Second&& second)
  {
    return second < first? std::forward<First>(first) : std::forward<Second>(second);
  }


  /// @brief Forward the maximal value between a1, a2 and args (by reference if it is passed by reference, by value otherwise).
  template <typename A1, typename A2, typename... Args>
  [[nodiscard]] constexpr decltype(auto) max(A1&& a1, A2&& a2, Args&&... args)
  {
    if constexpr (sizeof...(Args) == 1)
      return max(max(std::forward<A1>(a1), std::forward<A2>(a2)), std::forward<Args>(args)...);
    else
      return max(max(std::forward<A1>(a1), std::forward<A2>(a2)), max(std::forward<Args>(args)...));
  }


  /// @brief Forward the minimal value between first and second (by reference if it is passed by reference, by value otherwise).
  template <typename First, typename Second>
  [[nodiscard]] constexpr decltype(auto) min(First&& first, Second&& second)
  {
    return second < first? std::forward<Second>(second): std::forward<First>(first);
  }


  /// @brief Forward the minimal value between a1, a2 and args (by reference if it is passed by reference, by value otherwise).
  template <typename A1, typename A2, typename... Args>
  [[nodiscard]] constexpr decltype(auto) min(A1&& a1, A2&& a2, Args&&... args)
  {
    if constexpr (sizeof...(Args) == 1)
      return min(min(std::forward<A1>(a1), std::forward<A2>(a2)), std::forward<Args>(args)...);
    else
      return min(min(std::forward<A1>(a1), std::forward<A2>(a2)), min(std::forward<Args>(args)...));
  }

}

#endif//OGXX_PRIMITIVE_DEFINITIONS_HPP_INCLUDED
