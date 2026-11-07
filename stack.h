#pragma once
#include <cassert>
#include <vector>
#include <cstddef>

template <typename T>
class Stack
{
public:
    void push(const T &item)
    {
        items_.push_back(item);
    }
    void pop()
    {
        assert(!empty());
        items_.pop_back();
    }
    const T &top() const
    {
        assert(!empty());
        return items_.back();
    }
    bool empty() const { return items_.empty(); }
    std::size_t size() const { return items_.size(); }

private:
    std::vector<T> items_;
};