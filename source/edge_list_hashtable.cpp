#include <ogxx/io_head.hpp>
#include <ogxx/edge_list.hpp>
#include <unordered_set>
#include <iostream>

namespace ogxx {

struct Vertex_pair {
    Scalar_index first;
    Scalar_index second;

    Vertex_pair(Scalar_index f, Scalar_index s) : first(f), second(s) {}

    bool operator==(const Vertex_pair& other) const {
        return first == other.first && second == other.second;
    }
};

struct Vertex_pair_hash {
    std::size_t operator()(const Vertex_pair& p) const {
        std::hash<Scalar_index> h;
        return h(p.first) * 15485863 ^ h(p.second);
    }
};

class Edge_list_hashtable : public Edge_list, public St_set<Vertex_pair> {
private:
    std::unordered_set<Vertex_pair, Vertex_pair_hash> container;

public:
    Edge_list_hashtable() = default;

    void add_edge(Scalar_index vertex1, Scalar_index vertex2) override {
        Vertex_pair new_edge(vertex1, vertex2);
        container.insert(new_edge);
    }

    void remove_edge(Scalar_index vertex1, Scalar_index vertex2) override {
        Vertex_pair edge_to_remove(vertex1, vertex2);
        container.erase(edge_to_remove);
    }

    bool has_edge(Scalar_index vertex1, Scalar_index vertex2) const override {
        Vertex_pair edge_to_find(vertex1, vertex2);
        return container.find(edge_to_find) != container.end();
    }

    void clear_edges() override {
        container.clear();
    }

    void print_edges() const override {
        std::cout << "Edges in the hashtable:" << std::endl;
        for (const auto& edge : container) {
            std::cout << "(" << edge.first << ", " << edge.second << ")" << std::endl;
        }
    }

    // Реализация методов интерфейса St_set
    void insert(const Vertex_pair& value) override {
        container.insert(value);
    }

    void erase(const Vertex_pair& value) override {
        container.erase(value);
    }

    bool contains(const Vertex_pair& value) const override {
        return container.find(value) != container.end();
    }

    std::size_t size() const override {
        return container.size();
    }
};

} 
