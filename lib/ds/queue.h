#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START queue_fast
// Warning: O(pushed) space, no check start < size
template <typename T>
struct Queue {
    vector<T> a;
    size_t start = 0;
    Queue() {}

    void reserve(size_t n) {
        a.reserve(n);
    }
    void push(T x) {
        a.push_back(x);
    }
    void pop() {
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
