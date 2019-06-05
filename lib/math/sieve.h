#include <bits/stdc++.h>

using namespace std;

void solve() {
// SNIPPETS_START sieve
vector<int> prime;
auto sieve = [&](int _n = 45000){
    vector<bool> is(_n+1, true);
    is[0] = is[1] = false;
    for (int p = 2; p*p <= _n; p++) {
        if (is[p]) {
            for (int i = p*p; i <= _n; i += p) {
                is[i] = false;
            }
        }
    }
    for (int i = 2; i <= _n; i++) {
        if (is[i])
            prime.emplace_back(i);
    }
};
auto decomp = [&](int x){
    assert(x > 1);
    vector<pair<int, int>> res;
    for (int p: prime) {
        if (p*p > x) break;
        if (x % p == 0) {
            int e = 0;
            while (x % p == 0) {
                e++; x /= p;
            }
            res.emplace_back(p, e);
        }
    }
    if (x != 1)
        res.emplace_back(x, 1);
    return res;
};
auto divs = [&](int x){
    assert(x > 1);
    vector<int> res;
    res.emplace_back(1);
    for (auto& p: decomp(x)) {
        int b, e;
        tie(b, e) = p;
        int sz = res.size();
        int y = 1;
        while (e--) {
            y *= b;
            for (int i = 0; i < sz; i++) {
                res.emplace_back(res[i] * y);
            }
        }
    }
    return res;
};
// SNIPPETS_END
}
