#include "modular_sim.h"


// SNIPPETS_START mod_table_st
struct Comb {
    int n;
    vector<mint> fac, ifac, inv;

    Comb(int _n=1) {
        resize(2);
        fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
        n = 1; grow(_n);
    }

    void resize(int _s) {
        fac.resize(_s); ifac.resize(_s); inv.resize(_s);
    }
    bool grow(int _n) {
        if (_n <= n) return false;
        resize(_n+1);
        for (int i = n+1; i <= _n; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD/i) * inv[MOD%i];
            ifac[i] = ifac[i-1] * inv[i];
        }
        n = _n;
        return true;
    }
    // choose
    mint c(int N, int K) {
        if (N < K || K < 0) return 0;
        if (N > n) grow(N);
        return fac[N] * ifac[N-K] * ifac[K];
    }
    // sum x = S, x > 0
    mint p(int S, int K) {
        return c(S-1, K-1);
    }
    // sum x = S, x >= 0
    mint z(int S, int K) {
        return p(S+K, K);
    }
};
// SNIPPETS_END
