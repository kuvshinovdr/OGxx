/// @file Random_choice_bag #73.cpp
/// @brief the Random_choice_bag<T> class, which implements the Bag<T> interface and allows items to be retrieved in random order
/// @author Sutyagin A.I., nickname Alexanders2007, email asutagin062@gmail.com
#include <vector>
#include <random>

template<typename T>
class Random_choice_bag : public Bag<T> {
private:
    std::vector<T> elements;
    std::default_random_engine random_engine;

public:
    Random_choice_bag() {
        // Инициализация генератора случайных чисел
        std::random_device rd;
        random_engine = std::default_random_engine(rd());
    }

    void add(const T& element) override {
        elements.push_back(element);
    }

    T remove_random() override {
        if (elements.empty()) {
            throw std::runtime_error("Bag is empty");
        }

        // Генерация случайного индекса
        std::uniform_int_distribution<size_t> distribution(0, elements.size() - 1);
        size_t random_index = distribution(random_engine);

        // Обмен элемента с случайным индексом с последним элементом
        std::swap(elements[random_index], elements.back());

        // Удаление последнего элемента
        T removed_element = elements.back();
        elements.pop_back();

        return removed_element;
    }
};