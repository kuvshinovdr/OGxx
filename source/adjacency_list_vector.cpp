/// @file source/adjacency_list_vector.cpp
/// @brief Adjacency_list interface implementation over std::vector.
#include <ogxx/adjacency_list.hpp>
#include <ogxx/stl_iterator.hpp>
#include <vector>
#include <stdexcept>

namespace ogxx
{

  class Adjacency_list_vector
    : public Adjacency_list
  {
  public:
    Adjacency_list_vector() noexcept = default;

    // From Adjacency_list:

    auto degrees_sum() const noexcept
      -> Scalar_size   override
    {
      // TODO
      return 0;
    }

    auto get_vertex_count() const noexcept
      -> Scalar_size        override
    {
      return static_cast<Scalar_size>(_adj.size());
    }

    void set_vertex_count(Scalar_size new_vertex_count) override
    {
      Scalar_size const old_size = _adj.size();
      _adj.resize(new_vertex_count);
      if (new_vertex_count < old_size)
      {
        // TODO: удалить рёбра, ведущие к вершинам с индексами >= new_vertex_count
      }
    }

    // From List<Adjacency>

    void put(Scalar_index at, Pass_by<Adjacency> item) override
    {
      // TODO: insert
    }

    auto take(Scalar_index from)
      -> Pass_by<Adjacency> override
    {
      // TODO: erase
      return {};
    }

    // From Bag<Adjacency>

    void put(Pass_by<Adjacency> item) override
    {
      _adj.push_back(std::move(item));
    }

    auto take() -> Pass_by<Adjacency> override
    {
      if (_adj.empty())
        throw std::logic_error("Adjacency_list_vector::take: the list is empty");

      auto result = std::move(_adj.back());
      _adj.pop_back();
      return result;
    }

    void clear() override
    {
      _adj.clear();
    }

    // From Indexed_iterable<Adjacency>

    auto get(Scalar_index index) const
      -> See_by<Adjacency>        override
    {
      return _adj.at(index).get();
    }

    auto set(Scalar_index index, Pass_by<Adjacency> value)
      -> Pass_by<Adjacency> override
    {
      if (auto const needed_sz = static_cast<size_t>(index + 1); _adj.size() <= needed_sz)
        _adj.resize(needed_sz);

      auto old = std::move(_adj[index]);
      _adj[index] = std::move(value);
      return old;
    }

    // From Sized_iterable<Adjacency>

    auto size() const noexcept
      -> Scalar_size  override
    {
      return static_cast<Scalar_size>(_adj.size());
    }

    // From Iterable<Adjacency>

    auto iterate() const
      -> Basic_iterator_uptr<See_by<Adjacency>> override
    {
      using AdjVec  = std::vector<Adjacency_uptr>;
      using AdjIt   = AdjVec::const_iterator;
      using AdjCref = AdjVec::const_reference;

      return std::make_unique<Stl_iterator<
        Adjacency*, AdjIt, AdjIt, [](AdjCref up) { return up.get(); }>>
          (_adj.begin(), _adj.end());
    }

    auto is_empty() const noexcept
      -> bool       override
    {
      return _adj.empty();
    }

  private:
    std::vector<Adjacency_uptr> _adj;
  };

}
