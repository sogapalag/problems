#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START deque_fast
// Warning: no check start < size
template <typename T>
struct Deque {
    vector<T> a;
    size_t start = 0;
    Deque(size_t max_push_front) {
        a.resize(max_push_front);
        start = max_push_front;
    }

    void push_back(T x) {
        a.push_back(x);
    }
    void pop_back() {
        a.pop_back();
    }
    void push_front(T x) {
        a[--start] = x;
    }
    void pop_front() {
        ++start;
    }
    T& front() {
        return a[start];
    }
    T& back() {
        return a.back();
    }
    T& operator[](size_t i) {
        return a[start + i];
    }
    bool empty() const {
        return start == a.size();
    }
    size_t size() const {
        return a.size() - start;
    }
};
// SNIPPETS_END
