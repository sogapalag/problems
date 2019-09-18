#include "miller_rabin.h"

//https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/pollardsRho.html
// SNIPPETS_START pollard_rho
u64 mod_add(u64 x, u64 y, u64 m) {
    x += y;
    return x>=m? x-m: x;
}

u64 pollard_rho(u64 n, u64& c) {
    auto f = [&](u64 t){
        return mod_add(mod_mul(t,t,n), c, n);
    };
    while(true){
        u64 x=2, y=2;
        u64 d=1;
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(x<y?y-x:x-y, n);
        }
        if (d == n) {
            c++; continue;
        }
        return d;
    }
}

// [1, 2^64) 0.3 sec / 10^3
// [1, 2^32) 0.4 sec / 10^5
vector<pair<u64,u64>> factor(u64 n) {
    assert(n != 0);
    vector<pair<u64,u64>> res;
    static u64 WHEEL[] = {2, 3, 5, 7, 11, 13};
    for (const auto& p: WHEEL) {
        if (n%p == 0) {
            u64 e = 0;
            while (n%p == 0) {
                n /= p; e++;
            }
            res.emplace_back(p, e);
        }
    }
    if (n == 1) return res;

    vector<u64> pool;
    map<u64, u64> cnt;
    pool.emplace_back(n);
    u64 c = 1;
    while (!pool.empty()) {
        u64 n = pool.back(); pool.pop_back();
        if (miller_rabin(n)) {
            cnt[n]++; continue;
        }
        u64 d = pollard_rho(n, c);
        pool.emplace_back(d);
        pool.emplace_back(n/d);
    }
    for (auto& p: cnt) {
        res.push_back(p);
    }
    return res;
}
// SNIPPETS_END
