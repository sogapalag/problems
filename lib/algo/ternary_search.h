#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START ternary
template <typename T=double>
pair<T,T> ternary(T l, T r, function<T(T)> f, bool V=true) {
    int round = 400;
    while (round--) {
        T m0 = l + (r-l)/3;
        T m1 = r - (r-l)/3;
        T f0 = f(m0);
        T f1 = f(m1);

        if ((f0 < f1) ^ V) {
            l = m0;
        } else {
            r = m1;
        }
    }
    return {l, f(l)};
}
// SNIPPETS_END
