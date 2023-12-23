/// @file Random_choice_bag #73.cpp
/// @brief the Random_choice_bag<T> class, which implements the Bag<T> interface and allows items to be retrieved in random order
/// @author Sutyagin A.I., nickname Alexanders2007, email asutagin062@gmail.com
#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <vector>
#include <random>

namespace ogxx
{

template<typename T>
class Random_choice_bag : public Bag<T> {
private:
    std::vector<Pass_by<T>> elements;
    std::default_random_engine random_engine;

public:
    Random_choice_bag() // Инициализация генератора случайных чисел
      : random_engine(std::random_device{}()) {}

    explicit Random_choice_bag(Index_iterator_uptr items)
      : Random_choice_bag()
    {
        for (Scalar_index value; items->next(value);)
            elements.push_back(value);
    }

    void put(Pass_by<T> element) override {
        elements.push_back(element);
    }

    Pass_by<T> take() override {
        if (elements.empty()) {
            throw std::runtime_error("Random_choice_bag::take: the bag is empty");
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

    void clear() override
    {
        elements.clear();
    }

    auto iterate() const
      -> Basic_iterator_uptr<See_by<T>> override
    {  
        return new_stl_iterator(elements);
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

auto new_index_random_choice_bag() -> Index_bag_uptr
{
  return std::make_unique<Random_choice_bag<Scalar_index>>();
}

auto new_index_random_choice_bag(Index_iterator_uptr items) -> Index_bag_uptr
{
  return std::make_unique<Random_choice_bag<Scalar_index>>(std::move(items));
}

}
