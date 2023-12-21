#include <unordered_set>
#include <iostream>
#include <functional>

namespace ogxx {

// Определение типа Vertex_pair
struct Vertex_pair {
    int first;
    int second;

    // Добавим default конструктор
    Vertex_pair() : first(0), second(0) {}

    // Конструктор для удобства
    Vertex_pair(int f, int s) : first(f), second(s) {}

    // Оператор сравнения для использования в std::unordered_set
    bool operator==(const Vertex_pair& other) const {
        return first == other.first && second == other.second;
    }
};

// Хэш-функция для типа Vertex_pair
struct Vertex_pair_hash {
    std::size_t operator()(const Vertex_pair& p) const {
        std::hash<int> h;
        return h(p.first) * 15485863 ^ h(p.second);
    }
};

// Класс Edge_list_hashtable
class Edge_list_hashtable {
private:
    std::unordered_set<Vertex_pair, Vertex_pair_hash> container;

public:
    // Конструктор, который принимает параметры для инициализации
    Edge_list_hashtable(std::size_t table_size)
        : container(table_size) {}  

    // Метод для добавления ребра в список
    void add_edge(int vertex1, int vertex2) {
        Vertex_pair new_edge(vertex1, vertex2);

        // Используем хэш-таблицу для добавления ребра
        container.insert(new_edge);
    }

    // Метод для вывода всех рёбер
    void print_edges() const {
        std::cout << "Edges in the hashtable:" << std::endl;
        for (const auto& edge : container) {
            std::cout << "(" << edge.first << ", " << edge.second << ")" << std::endl;
        }
    }
};

} // namespace ogxx

int main() {
    ogxx::Edge_list_hashtable graph(10); 

    // Add edges to the graph
    graph.add_edge(1, 2);
    graph.add_edge(3, 4);
    graph.add_edge(1, 2); 

    graph.print_edges();

    return 0;
}
