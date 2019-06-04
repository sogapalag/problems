#include "modular_sim.h"
// fast fac/ inv/ ifac table, for binomial using.
// O(n), instead of 1/i use *log(n)

void solve() {
    int n = 100;
// SNIPPETS_START mod_table
int _n = n;
vector<mint> fac(_n+1);
vector<mint> ifac(_n+1);
vector<mint> inv(_n+1);
auto build = [&](){
    fac[0] = fac[1] = 1;
    ifac[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= _n; i++) {
        fac[i] = fac[i-1] * i;
        inv[i] = (-MOD/i) * inv[MOD%i];
        ifac[i] = ifac[i-1] * inv[i];
    }
};
build();
// SNIPPETS_END
}
