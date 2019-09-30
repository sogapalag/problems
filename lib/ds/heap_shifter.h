#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START heap_shifter
template <typename Heap>
struct Shifter {
    using T=typename Heap::value_type;

    Heap h;
    T s=0;
    // shift all vals current in heap +x.
    void shift(T x) {
        s += x;
    }
    void push(T x) {
        h.push(x - s);
    }
    T top() {
        return h.top() + s;
    }
    void pop() {
        h.pop();
    }
};
template<class T> using MaxHeap = Shifter<priority_queue<T>>;
template<class T> using MinHeap = Shifter<priority_queue<T, vector<T>, greater<T>>>;
// SNIPPETS_END
