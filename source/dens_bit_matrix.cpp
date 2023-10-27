/// @file dense_bit_matrix.cpp
/// @brief Dense bit matrix + 'next' method.
/// @author Tsay A.
#include "matrix.hpp"

namespace ogxx {
    class Dense_bit_iterator : public Basic_iterator<bool> {
    public:
        
        Dense_bit_iterator(unsigned const* word, int firstbit, int endbit)
            : word(word), currentbit(firstbit), endbit(endbit) {}
        //@brief 'next' method
        Dense_bit_iterator next() 
        {
            if (currentbit < lastbit)
            {
                ++currentbit;
            }
            else currentbit = 0;
            return *this;
        }
    private:
        unsigned const* word;
        int currentbit;
        int lastbit;
        int stride = 1;
    };
}