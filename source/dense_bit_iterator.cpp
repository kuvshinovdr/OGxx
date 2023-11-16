/// @file dense_bit_iterator.cpp
/// @brief Dense bit iterator + 'next' method.
/// @author Tsay A.
#include <ogxx/iterator.hpp>
#include <climits>

constexpr unsigned word_bits = sizeof(unsigned) * CHAR_BIT;

namespace ogxx
{

class Dense_bit_iterator : public Basic_iterator<bool> 
{
public:
    Dense_bit_iterator(
      unsigned const* word, 
      size_t          firstbit, 
      size_t          endbit, 
      size_t          stride = 1
    )
      : word(word), currentbit(firstbit), endbit(endbit), stride(stride) {}

    /// @brief 'next' method
    bool next(bool& value) noexcept override {
        if (currentbit >= endbit)
          return false;

        value = (word[currentbit / word_bits] >> (currentbit % word_bits)) & 1;
        currentbit += stride;
        return true;
    }

private:
    unsigned const* word;
    size_t currentbit;
    size_t endbit;
    size_t stride = 1;
};

}
