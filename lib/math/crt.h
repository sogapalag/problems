#include <bits/stdc++.h>

using namespace std;

// https://crypto.stanford.edu/pbc/notes/numbertheory/crt.html
// crt: m1=n1^-1 (mod m2). by exgcd. so res work
// excrt: res formula obviously sat for a1, replace n1m1=g-n2m2 get the similar formula for a2.

// SNIPPETS_START crt
template <typename T=int>
T exgcd(T a, T b, T& x, T& y) {
    if (!a) { x = 0; y = 1; return b; }
    T d = exgcd(b%a, a, y, x);
    x -= b/a * y;
    return d;
}
// watch out potential overflow!
template <typename T>
T crt(T a1, T a2, T n1, T n2) {
    T m1, m2;
    assert(exgcd<T>(n1,n2,m1,m2) == 1);
    T z = n1*n2;
    T res = (__int128)a1*m2%z*n2 %z + (__int128)a2*m1%z*n1 %z;
    ((res%=z)+=z)%=z;
    assert(res%n1 == a1%n1);
    assert(res%n2 == a2%n2);
    return res;
}

template <typename T>
T excrt(T a1, T a2, T n1, T n2) {
    T m1, m2;
    T g = exgcd<T>(n1,n2,m1,m2);
    assert(abs(a1-a2) % g == 0);
    T z = n1*n2/g;
    T res = a1 - (__int128)n1*m1%z*((a1-a2)/g)%z;
    ((res%=z)+=z)%=z;
    assert(res%n1 == a1%n1);
    assert(res%n2 == a2%n2);
    return res;
}
// SNIPPETS_END
