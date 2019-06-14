#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
T exgcd(T a, T b, T& x, T& y) {
    if (!a) { x = 0; y = 1; return b; }
    T d = exgcd(b%a, a, y, x);
    x -= b/a * y;
    return d;
}
