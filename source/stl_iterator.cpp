#include "../include/iterator.hpp"
#include <iostream>

using namespace std;

template <typename T, typename It, typename Sent>
class Stl_iterator : public ogxx::Basic_iterator<T>{
    private: 
    It current;
    Sent end;
    public:
        Stl_iterator(It a, Sent b)
        {
            current = a;
            end = b;
        };
        template <typename Cont>
        Stl_iterator(Cont& a)
        {
            current = std::begin(a);
            end = std::end(a);
        };
        bool next(T& out_item) noexcept
        {
            if (current == end) return false;
            out_item = *current;
            current++;
            return true;
        };
};

