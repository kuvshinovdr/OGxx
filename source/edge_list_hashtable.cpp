#include <unordered_set>  // for std::unordered_set
#include <algorithm>      // for std::max_element
#include <utility>        // for std::pair (if Vertex_pair is std::pair)

#include <ogxx/edge_list.hpp>  // for ogxx::Edge_list
#include <ogxx/st_set.hpp>     // for ogxx::St_set
#include <ogxx/vertex_pair.hpp> // if Vertex_pair is defined in this file

// Define the hash function for Vertex_pair
namespace std {
  template <typename T1, typename T2>
  struct hash<pair<T1, T2>> {
    auto operator()(const pair<T1, T2> &p) const -> size_t {
      return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
    }
  };
}

namespace ogxx {
  class Edge_list_hashtable : public Edge_list, public St_set<Vertex_pair> {
  public:
    auto contains(Vertex_pair item) const noexcept -> bool override {
      return edges.count(item) > 0;
    }

    auto insert(Vertex_pair item) -> bool override {
      auto [iter, inserted] = edges.insert(item);
      return inserted;
    }

    auto erase(Vertex_pair item) -> bool override {
      return edges.erase(item) > 0;
    }

    auto find(Vertex_pair edge) const noexcept -> Scalar_index override {
      auto iter = edges.find(edge);
      if (iter != edges.end()) {
        return std::distance(edges.begin(), iter);
      }
      return ogxx::npos;
    }

    auto max_vertex_index() const noexcept -> Vertex_index override {
      if (edges.empty()) {
        return -1;
      }
      auto max_index_iter = std::max_element(edges.begin(), edges.end(),
        [](const Vertex_pair& a, const Vertex_pair& b) {
          return std::max(a.first, a.second) < std::max(b.first, b.second);
        });
      return std::max(max_index_iter->first, max_index_iter->second);
    }

  private:
    std::unordered_set<Vertex_pair> edges;
  };
}
