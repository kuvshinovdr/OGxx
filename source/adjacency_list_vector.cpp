/// @file source/adjacency_list_vector.cpp
/// @brief Adjacency_list interface implementation over std::vector.
#include <ogxx/adjacency_list.hpp>
#include <ogxx/stl_iterator.hpp>
#include <vector>
#include <stdexcept>

namespace ogxx
{

  namespace
  {
    using Adjacency_list_vector_storage
      = std::vector<std::unique_ptr<Adjacency>>;

    class Adjacency_list_vector_iterator
      : public Basic_iterator<See_by<Adjacency_list_entry>>
    {
    public:
      Adjacency_list_vector_iterator(
        Adjacency_list_vector_storage const& vector)
        : _begin(vector.begin()), _end(vector.end()) {}

      auto next(See_by<Adjacency_list_entry>& value) noexcept
        -> bool override
      {
        if (_begin == _end)
          return false;

        value.vertex    = _cur++;
        value.adjacency = _begin->get();
        ++_begin;
        return true;
      }

    private:
      Adjacency_list_vector_storage::const_iterator 
        _begin,
        _end;

      Vertex_index _cur = 0;
    };
  }

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

    void clear() override
    {
      _adj.clear();
    }

    // From Indexed_iterable<Adjacency>

    auto get(Scalar_index index)      const
      -> See_by<Adjacency_list_entry> override
    {
      return { index, _adj.at(index).get() };
    }

    auto set(
      Scalar_index                  index, 
      Pass_by<Adjacency_list_entry> value)
        -> Pass_by<Adjacency_list_entry> override
    {
      if (auto const needed_sz = static_cast<size_t>(index + 1); _adj.size() <= needed_sz)
        _adj.resize(needed_sz);

      _adj[index].reset(value.adjacency);
      return { index }; // TODO: fail to return the old adjacency.
      // We return nullptr because it is forbidden to
      // transfer ownership by passing an ordinary pointer.
    }

    // From Sized_iterable<Adjacency>

    auto size() const noexcept
      -> Scalar_size  override
    {
      return static_cast<Scalar_size>(_adj.size());
    }

    // From Iterable<Adjacency>

    auto iterate() const
      -> Basic_iterator_uptr<See_by<Adjacency_list_entry>> override
    {
      return std::make_unique<Adjacency_list_vector_iterator>(_adj);
    }

    auto is_empty() const noexcept
      -> bool       override
    {
      return _adj.empty();
    }

  private:
    Adjacency_list_vector_storage _adj;
  };

}
