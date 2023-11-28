/// @file dense_bit_iterator.cpp
/// @brief Dense bit iterator + 'next' method.
/// @author Tsay A.
#include <ogxx/iterator.hpp>
#include <climits>

namespace ogxx
{

  constexpr unsigned word_bits = sizeof(unsigned) * CHAR_BIT;

  class Dense_bit_iterator 
    : public Bit_iterator 
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


  auto new_dense_bit_iterator(
    unsigned const* word,
    size_t          firstbit,
    size_t          endbit,
    size_t          stride)
      -> Bit_iterator_uptr
  {
    return std::make_unique<Dense_bit_iterator>(word, firstbit, endbit, stride);
  }

}
