/// @file index_set_bitvector.cpp
/// @brief Defining interfaces for bitvector
/// @author Ivan I. Martynov <7martyn1>
#include <ogxx/st_set.hpp>
#include <ogxx/iterable.hpp>

#include <vector>


namespace ogxx {
  template <typename Scalar_index>
  class Index_set_bitvector : public Index_set, public Indexed_iterable<Scalar_index> {
    private:
      std::vector<bool> bits;

    public:
      Index_set_bitvector() = default;

      bool contains(Scalar_index index) const override {
        if (index < bits.size()) {
          return bits[index];
        }
        return false;
      }


      bool insert(Scalar_index item) override
      {
        if (index >= bits.size())
          bits.resize(index + 1, false);

        if (bits[item])
          return false;

        bits[item] = true;
        return true;
      }

      void set(const Scalar_index& index, bool value) override
      {
        bits[index] = value;
      }

      bool get(const Scalar_index& index) const override
      {
        return bits[index];
      }

      bool is_empty() const override
      {
        return bits.empty();
      }

      void iterate(const function<void(const Scalar_index&)>& func) const override
      {
        for (const auto& index : bits)
        {
            func(index);
        }
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



  };
}