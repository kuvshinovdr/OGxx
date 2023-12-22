/// @file source/adjacency_list_hashtable.cpp
/// @brief Adjacency_list interface implementation over std::unordered_map.
#include <ogxx/adjacency_list.hpp>
#include <ogxx/stl_iterator.hpp>
#include <unordered_map>
#include <stdexcept>


namespace ogxx
{
  // Функция для преобразования pair в map в Adjacency_list_entry
  Adjacency_list_entry convertToEntry(const std::pair<const Scalar_index, std::unique_ptr<Adjacency>>& pair) {
    return Adjacency_list_entry{pair.first, pair.second.get()};
  }
  class Adjacency_list_hashtable: public Adjacency_list
  {
    private:
      std::unordered_map<Scalar_index, std::unique_ptr<Adjacency>> _adj;      
    public:
      Adjacency_list_hashtable() noexcept = default;
      ~Adjacency_list_hashtable() noexcept = default;

      auto degrees_sum() const noexcept
      -> Scalar_size override{
        Scalar_size sum = 0;
        for (const auto& pair : _adj){
          sum += pair.second->size();
        }
        return sum;
      }

      auto get_vertex_count() const noexcept
      -> Scalar_size override{
        return static_cast<Scalar_size>(_adj.size());
      }

      void set_vertex_count(Scalar_size new_vertex_count) override{
        if (new_vertex_count < _adj.size()){
          for (auto it = _adj.begin(); it != _adj.end();){
            if (it->first >= new_vertex_count){
              it = _adj.erase(it);
            }
            else{
              ++it;
            }
          }
        }
      }

    void clear() override
    {
      _adj.clear();
    }

  auto get(Scalar_index index) const
  -> See_by<Adjacency_list_entry> override{
    auto it = _adj.find(index);
    if (it == _adj.end())
    {
      throw std::out_of_range("Adjacency_list_hashtable::get: Index out of range");
    }
    return Adjacency_list_entry{index, it->second.get()};
  }

  auto set(Scalar_index index, Pass_by<Adjacency_list_entry> value)
  -> Pass_by<Adjacency_list_entry> override
  {
    auto it = _adj.find(index);
    if (it == _adj.end())
    {
      throw std::out_of_range("Adjacency_list_hashtable::set: Index out of range");
    }
    auto old_value = Adjacency_list_entry{index, it->second.release()};
    it->second.reset(value.adjacency);
    return old_value;
  }

    auto size() const noexcept
      -> Scalar_size  override
    {
      return static_cast<Scalar_size>(_adj.size());
    }

    auto iterate() const
    -> Basic_iterator_uptr<See_by<Adjacency_list_entry>> override {
      using MapIter = decltype(_adj.cbegin());
      using MapSent = decltype(_adj.cend());
      using Entry = Adjacency_list_entry;
      using Iter = Stl_iterator<Entry, MapIter, MapSent, convertToEntry>;
      return std::make_unique<Iter>(_adj.cbegin(), _adj.cend());
}

    auto is_empty() const noexcept
      -> bool override
    {
      return _adj.empty();
    }

  };
  
      
}

