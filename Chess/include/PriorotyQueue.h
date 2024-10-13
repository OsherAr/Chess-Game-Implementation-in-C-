#pragma once
#include <list>
#include <algorithm>

template <typename T, typename Comparator>
class PriorityQueue {
public:
    explicit PriorityQueue(size_t maxSize) : maxSize(maxSize) {}

    void push(const T& value) {
        queue.push_back(value);
        queue.sort(Comparator());
        if (queue.size() > maxSize) {
            queue.pop_back();  // Remove the least priority element
        }
    }

    T poll() {
        T top = queue.front();
        queue.pop_front();
        return top;
    }

    bool isEmpty() const {
        return queue.empty();
    }

private:
    std::list<T> queue;
    size_t maxSize;
};
