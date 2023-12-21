/// @file Random_choice_bag #73.cpp
/// @brief the Random_choice_bag<T> class, which implements the Bag<T> interface and allows items to be retrieved in random order
/// @author Sutyagin A.I., nickname Alexanders2007, email asutagin062@gmail.com
#include <vector>
#include <random>
#include <ogxx>

template<typename T>
class Random_choice_bag : public Bag<T> {
private:
    std::vector<Pass_by<T>> elements;
    std::default_random_engine random_engine;

public:
    Random_choice_bag() // Инициализация генератора случайных чисел
      : random_engine(std::random_device{}()) {}

    void put(Pass_by<T> element) override {
        elements.push_back(element);
    }

    Pass_by<T> take() override {
        if (elements.empty()) {
            throw std::runtime_error("Bag is empty");
        }

        // Генерация случайного индекса
        std::uniform_int_distribution<size_t> distribution(0, elements.size() - 1);
        size_t random_index = distribution(random_engine);

        // Обмен элемента с случайным индексом с последним элементом
        std::swap(elements[random_index], elements.back());

        // Удаление последнего элемента
        auto removed_element = std::move(elements.back());
        elements.pop_back();

        return removed_element;
    }

    auto iterate() const
      ->Basic_iterator_uptr<See_by<T>> override
    {  
      using IteratorType = typename std::vector<Pass_by<T>>::const_iterator; 
      auto iterator = std::make_unique<STL_iterator<IteratorType>>(elements.begin(), elements.end()); 
      return iterator; 
    }

    auto is_empty() const noexcept
      -> bool override
    {
      return elements.empty();
    }

    auto size() const noexcept
      -> Scalar_size override
    {
      return elements.size();
    }
};