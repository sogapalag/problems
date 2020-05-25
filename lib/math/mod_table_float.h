#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START mod_table_float
// Caution all log. call exp(x) for recover
struct Comb {
    using T = double; // long double;
    int N;
    vector<T> fac;

    Comb(int _n=1) {
        resize(2);
        fac[0] = fac[1] = 0;
        N = 1; grow(_n);
    }

    void resize(int _s) {
        fac.resize(_s);
    }
    bool grow(int _n) {
        if (_n <= N) return false;
        swap(_n, N); resize(N+1);
        for (int i = _n+1; i <= N; i++) {
            fac[i] = fac[i-1] + log((T)i);
        }
        return true;
    }
    // perm
    T a(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] - fac[n-k];
    }
    // choose
    T c(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] - fac[n-k] - fac[k];
    }
    // sum x = s, x > 0
    T p(int s, int k) {
        if (s==0&&k==0)return 1;
        return c(s-1, k-1);
    }
    // sum x = s, x >= 0
    T z(int s, int k) {
        return p(s+k, k);
    }
    // \E Y-X >= m
    T hit(int n, int k, int m=1) {
        if (m <= k-n) return c(n+k, n);
        return c(n+k, k-m);
    }
    // catalan trapezoids C_m(n, k)
    // \A Y-X < m,  =c(n+k,n) - hit
    //T cat(int n, int k, int m=1) {
    //    if (m > k) return c(n+k, n);
    //    if (m <= k-n) return 0;
    //    // c-c, !! call exp(c)
    //    return c(n+k,n) - c(n+k, k-m);
    //}
};
// SNIPPETS_END
