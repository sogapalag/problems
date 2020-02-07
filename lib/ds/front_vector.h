#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START front_vector
template <typename T>
struct FrontVector {
    vector<T> a;
    FrontVector() {}
    FrontVector(int n, const T& x = T()) : a(n, x) {}

    void push_front(T x) {
        a.push_back(x);
    }
    void pop_front() {
        a.pop_back();
    }
    T& front() {
        return a.back();
    }
    bool empty() const {
        return a.empty();
    }
    size_t size() { return a.size(); }
    T& operator[](size_t i){
        return a[size()-i-1];
    }
};
// SNIPPETS_END
