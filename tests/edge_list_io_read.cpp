/// @file edge_list_io_read.cpp
/// @brief Testing the function "read" in the edge_list_io_read.cpp
/// /// @author Artemenko I.V
#include "testing_head.hpp"
#include <source/parsing_utils.hpp>
#include <edge_list_io_read.cpp>
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

 
