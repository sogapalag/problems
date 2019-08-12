#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START pow
template <typename T>
T pow(T x, int64_t e) {
    T res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res *= x;
        x *= x;
    }
    return res;
}
// SNIPPETS_END
