#include <bits/stdc++.h>

using namespace std;
#define int ll
using ll=long long ;

// k odd, 1, 3_, 5, 7, 9_, ... C at_ 3x(1,3,5..)
// k even, 2, 4, 6_, 8, 10, 12_,... C at_ 3x(2,4,6,...)
// so count those _ cannot not block by others
//
// if k % 3==0, res = 0, obvious.
// if k odd, then (1,3,5,...) coprime to k is answer. which = #f(m, 2*k), i.e. fill vitual 2s eliminate.
// if k even, two situations, k has 2^1 or 2^{>1}
//    2^1, note (2,4,6...) = 2(1,2,3...m), so odds in [m] in blocked, since k/2 is odd too.
//          where (x,y) both odd definitely in.
//          so possibles in 2(2, 4, 6,...)= 4(1,2,3,...m/2), but this is not enough,
//              since if they dividy by d, (x,y) is even still blocked.
//          so they need co coprime to k/2. i.e. f(m/2, k/2)
//    2^{>1}, first 3*2(1,2,3...m) those even in [m] is blocked, since (x,y=k/2) both even.
//          then (1,3,5,..) only need to coprime to k. i.e. f(m, k) similar to k odd case.
void solve() {
    ll n;  cin >> n;
    if (n == 1) {
        cout << 1; return;
    }
    ll k = (n+3)/2;
    
    vector<int> prime;
    auto sieve = [&](int _n = 120000){
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
    // count [1..=m] coprime to c
    auto f = [&](int m, int c){
        int tmp = 0;
        vector<int> di;
        for (auto& p: decomp(c)) {
            di.emplace_back(p.first);
        }
        int sz = di.size();
        for (int msk = 1; msk < (1<<sz); msk++) {
            int prod = 1;
            for (int k = 0; k < sz; k++) {
                if (msk & (1<<k)) {
                    prod *= di[k];
                }
            }
            int sign = (__builtin_popcount(msk)&1)? 1: -1;
            tmp += sign * m/prod;
        }
        return m - tmp;
    };
    sieve();
    // not only C, AB can block too
    int res;
    if (k&1){
        int m = (k-1)/3;
        if (k % 3 == 0) {
            res = 0;
        }else {
            res = f(m, 2*k) * 2;
        }
    } else {
        if (k % 3 == 0) {
            res = 0;
        } else {
            int m = (k-1)/6;
            int e = decomp(k)[0].second;
            if (e == 1) {
                //res = (m/2) * 2;
                //res += f(m, k) * 2;
                res = f(m/2, k/2) * 2;
            } else {
                //res = (m - m/2) * 2;
                res = f(m, k/2) * 2;
            }
        }
    }
    cout << res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
