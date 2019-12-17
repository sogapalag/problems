#include "modular_sim.h"

// SNIPPETS_START table_stirling
// [n k]: n into k cycles 
vector<vector<mint>> stir_first(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*(i-1);
        }
    }
    return stir;
}
// {n k}: n into k sets
vector<vector<mint>> stir_second(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*j;
        }
    }
    return stir;
}
// using, x^n = sum_{k:0..=n} {n k} (x)_k
// (x)_n := x*(x-1)...(x-n+1)
vector<mint> fall_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x-i+1);
    }
    return res;
}
vector<mint> rise_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x+i-1);
    }
    return res;
}
// SNIPPETS_END

// by wiki
//mint stir2(int n, int k) {
//    mint sum = 0;
//    int sign = 1;
//    for (int i = 0; i <= k; i++) {
//        sum += sign * c.c(k,i) * mint(k-i).exp(n);
//        sign *= -1;
//    }
//    return sum * c.ifac[k];
//}
