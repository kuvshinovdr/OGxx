#include <unordered_set>  // for std::unordered_set
#include <algorithm>      // for std::max_element
#include <utility>        // for std::pair (if Vertex_pair is std::pair)

#include <ogxx/edge_list.hpp>  // for ogxx::Edge_list
#include <ogxx/st_set.hpp>     // for ogxx::St_set
#include <ogxx/vertex_pair.hpp> // if Vertex_pair is defined in this file

// Define the hash function for Vertex_pair
namespace std {
  template <typename T1, typename T2>
  struct hash<ogxx::Vertex_pair> {
    auto operator()(ogxx::Vertex_pair p) const noexcept {
        hash<ogxx::Scalar_index> h;
        return h(p.first) * sqr(15485863, h(p.second));
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
		  // TODO: this is (a worser) linear search, can we do better?
        return std::distance(edges.begin(), iter);
      }
      return ogxx::npos;
    }

    auto max_vertex_index() const noexcept -> Vertex_index override {
      if (edges.empty()) {
        return -1;
      }
	  // TODO: this will not compile
      auto max_index_iter = std:max(std:max(edges.begin().first, edges.end().first), std::max(edges.begin().second, edges.end().second));
      return max_index_iter;
    }
	
	// TODO: not all methods are overriden.

  private:
    std::unordered_set<Vertex_pair> edges;
  };
}
