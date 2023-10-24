/// @file parsing_utils.hpp
/// @brief Utility functions to make text parsing easier.
/// @author Kuvshinov D.R. kuvshinovdr at yandex.ru
#ifndef OGXX_PARSING_UTILS_HPP_INCLUDED
#define OGXX_PARSING_UTILS_HPP_INCLUDED

#include <ogxx/io_head.hpp>
#include <ogxx/primitive_definitions.hpp>


/// @brief Utility functions intended to facilitate IO implementations.
namespace ogxx::io::util
{

  /// @brief Space characters used as token separators.
  constexpr string_view token_separators = " \n\r\t"sv;

  /// @brief Remove maximal prefix consisting of token_separators.
  /// @param sv string_view to be trimmed from the left
  /// @return sv
  inline auto ltrim(string_view& sv)
    -> string_view&
  {
    sv.remove_prefix(min(sv.size(), sv.find_first_not_of(token_separators)));
    return sv;
  }

  /// @brief Get next token and remove the corresponding prefix from tokens.
  /// E.g. extract_next_token(tokens = " alpha beta") returns "alpha" and tokens becomes " beta" then.
  /// @param tokens string_view with tokens separated with token_separators characters
  /// @return the token that was removed
  inline auto extract_next_token(string_view& tokens)
    -> string_view
  {
    auto const pos = ltrim(tokens).find_first_of(token_separators);
    auto const res = tokens.substr(0, pos);
    tokens.remove_prefix(res.size());
    return res;
  }

  /// @brief Check if input contains a sequence of tokens and remove those tokens from input.
  /// E.g. accept_tokens(input = "bit_matrix{\n00111\n}", "bit_matrix {") returns true and
  /// input becomes "\n00111\n}" then. 
  /// @param input  a sequence of characters to be tested, maximal coinciding prefix will be removed from input
  /// @param tokens a sequence of tokens that are expected in the input
  /// @return true if all tokens have been found in input, false otherwise
  inline auto accept_tokens(string_view& input, string_view tokens) noexcept
    -> bool
  {
    for (string_view token; !(token = extract_next_token(tokens)).empty();)
    {
      if (!ltrim(input).starts_with(token))
        return false;
      input.remove_prefix(token.size());
    }

    return true;
  }

}

#endif//OGXX_PARSING_UTILS_HPP_INCLUDED
