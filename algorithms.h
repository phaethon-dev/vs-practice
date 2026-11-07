#pragma once
#include <cassert>
#include <vector>

template <typename T> const T &maxOf(const std::vector<T> &items){
    assert(!items.empty());
    const T *max = &items[0];
    for (const auto &item : items) {
        if (*max < item) {
            max = &item;
        }
    }
    return *max;
}

template <typename T> T sumOf(const std::vector<T> &items){
    T sum = T();
    for (const auto &item : items) {
        sum += item;
    }
    return sum;
}