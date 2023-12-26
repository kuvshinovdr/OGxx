/// @file Stack-Queue-Mixed_stack_queue.cpp
/// @brief Implementation of the Stack<T>, Queue<T>, Mixed_stack_queue<T> classes implementing Bag<T>
/// @author Shemyakin D.V.

#include <ogxx/iterable.hpp>
#include <ogxx/stl_iterator.hpp>
#include <deque>
#include <random>

namespace ogxx{
    template <typename T>
    class Stack : public Bag<T> {
    private:
        std::deque<Pass_by<T>> data;

    public:
        void put(Pass_by<T> item) override {
            data.push_back(item);
        }

        auto take() -> Pass_by<T> override {
            if (!this->is_empty()) {
                Pass_by<T> item = std::move(data.back());
                data.pop_back();
                return item;
            }
            throw std::runtime_error("Stack::take: the stack is empty");
        }

        void clear() override {
            data.clear();
        }
    };

    template <typename T>
    class Queue : public Bag<T> {
    private:
        std::deque<Pass_by<T>> data;

    public:
        void put(Pass_by<T> item) override {
            data.push_back(item);
        }

        auto take() -> Pass_by<T> override {
            if (!this->is_empty()) {
                Pass_by<T> item = std::move(data.front());
                data.pop_front();
                return item;
            }
            throw std::runtime_error("Queue::take: the queue is empty");
        }

        void clear() override {
            data.clear();
        }
    };

    template <typename T>
    class Mixed_stack_queue : public Bag<T> {
    private:
        std::deque<Pass_by<T>>       data;
		std::default_random_engine   rng;
		std::bernoulli_distribution  distr;

    public:
        explicit Mixed_stack_queue(double probability = 0.5) 
		    : distr(probability), rng(std::random_device{}()) {}

        void put(Pass_by<T> item) override {
            data.push_back(item);
        }

        auto take() -> Pass_by<T> override {
            if (!this->is_empty()) {
                if (distr(rng)) {
                    Pass_by<T> item = std::move(data.back());
                    data.pop_back();
                    return item;
                } else {
                    Pass_by<T> item = std::move(data.front());
                    data.pop_front();
                    return item;
                }
            }
            throw std::runtime_error("Mixed_stack_queue::take: the queue is empty");
        }

        void clear() override {
            data.clear();
        }
    };
}
