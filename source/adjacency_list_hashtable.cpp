/// @file source/adjacency_list_hashtable.cpp
/// @brief Adjacency_list interface implementation over std::unordered_map.
#include <ogxx/adjacency_list.hpp>
#include <ogxx/stl_iterator.hpp>
#include <unordered_map>
#include <stdexcept>

namespace ogxx
{
  class Adjacency_list_hashtable: public Adjacency_list
  {
    private:
      std::unordered_map<Scalar_index, std::unique_ptr<Adjacency>> _adj;
    public:
      Adjacency_list_hashtable() noexcept = default;
      ~Adjacency_list_hashtable() noexcept = default;
    // From Adjacency_list:

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

    // From Indexed_iterable<Adjacency>

    auto get(Scalar_index index) const
    -> See_by<Adjacency> override
    {
      auto it = _adj.find(index);
      if (it == _adj.end())
      {
        throw std::out_of_range("Index out of range");
      }
      return it->second.get();
    }

    auto set(Scalar_index index, Pass_by<Adjacency> value)
    -> Pass_by<Adjacency> override
    {
      auto it = _adj.find(index);
      if (it == _adj.end())
      {
        throw std::out_of_range("Index out of range");
      }
      auto old_value = std::move(it->second);
      it->second = std::move(value);
      return old_value;
    }

    // From Sized_iterable<Adjacency>

    auto size() const noexcept
      -> Scalar_size  override
    {
      return static_cast<Scalar_size>(_adj.size());
    }

    // From Iterable<Adjacency>

    auto iterate() const
    -> Basic_iterator_uptr<See_by<Adjacency>> override{
      throw std::runtime_error("iterate() is not implemented yet");
    }


    auto is_empty() const noexcept
      -> bool override
    {
      return _adj.empty();
    }

  
  };
}