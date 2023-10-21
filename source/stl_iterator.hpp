///  stl_iterator.hpp
/// This file defines the Stl_iterator class, which provides an iterator for standard C++ containers.
/// ChernyshevMV
#ifndef OGXX_STL_ITERATOR_HPP
#define OGXX_STL_ITERATOR_HPP
#include <iterator>
 #include <OGXX/source/stl_iterator.hpp>
namespace ogxx {
template <typename T, typename It, typename Sent>
class Stl_iterator : public Basic_iterator<T> {
private:
    It current;
    Sent end;
public:
    Stl_iterator(It a, Sent b) : current(a), end(b) {}   
    template <typename Cont>
    Stl_iterator(Cont& a) : current(std::begin(a)), end(std::end(a)) {}
    bool next(T& out_item) noexcept override {
        if (current == end) return false;
        out_item = *current;
        ++current;
        return true;
    }
};
}  
#endif