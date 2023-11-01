/// @file dense_bit_iterator.cpp
/// @brief Dense bit iterator + 'next' method.
/// @author Tsay A.
class Dense_bit_iterator : public Basic_iterator<bool> 
{
public:
    Dense_bit_iterator(unsigned const* word, size_t firstbit, size_t endbit)
        : word(word), currentbit(firstbit), endbit(endbit) {}
    ~Dense_bit_iterator() {}

    //@brief 'next' method
    bool next(bool& value) noexcept override {
        if (currentbit < endbit)
        {
        value = word[currentbit];
        currentbit += stride;
        return true;
        }
        else return false;
    }
private:
    unsigned const* word;
    size_t currentbit;
    size_t endbit;
    size_t stride = 1;
}
