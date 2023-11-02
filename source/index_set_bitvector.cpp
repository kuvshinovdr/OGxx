
/// @file index_set_bitvector.cpp
/// @brief Defining interfaces for bitvector
/// @author Ivan I. Martynov <7martyn1>

#ifndef OGXX_BIT_MATRIX_HPP_INCLUDED
#define OGXX_BIT_MATRIX_HPP_INCLUDED


#include <vector>
#include <ogxx/index_set.h>
#include <ogxx/indexed_iterable.h>

namespace ogxx {
  template <typename Scalar_index>
  class Index_set_bitvector : public Index_set, public Indexed_iterable<Scalar_index> {
    private:
      std::vector<bool> bits;

    public:
      Index_set_bitvector() = default;

      void add(const Scalar_index& index) override {
        if (index >= bits.size()) {
          bits.resize(index + 1, false);
        }
        bits[index] = true;
      }

      void remove(const Scalar_index& index) override {
        if (index < bits.size()) {
          bits[index] = false;
        }
      }

      bool contains(Scalar_index index) const override {
        if (index < bits.size()) {
          return bits[index];
        }
        return false;
      }


      bool insert(Scalar_index item) override
      {
        // if item >= size() then resize
        if (bits[item])
          return false;

        bits[item] = true;
        return true;
      }
        

      bool erase(Scalar_index item) override
      {
        if (item >= bits.size())
          return false;
        
        if (bits[item])
        {
          bits[item] = false;
          return true;
        }
        
        return false;
      }


      void clear() override {
        bits.clear();
      }

      size_t size() const override {
        return bits.size();
      }

      std::vector<Scalar_index> indices() const {
        std::vector<Scalar_index> result;
        for (Scalar_index i = 0; i < bits.size(); ++i) {
          if (bits[i]) {
            result.push_back(i);
          }
        }
        return result;
      }

  };
}
#endif//OGXX_BIT_MATRIX_HPP_INCLUDED