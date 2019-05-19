#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START bs_first
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_fisrt(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
// SNIPPETS_END