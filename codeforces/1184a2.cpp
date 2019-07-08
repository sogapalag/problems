#include <bits/stdc++.h>

using namespace std;


// k valid iff index, i, i+k, i+2k, ...,  sum(^) = 0. since for x0, we can set x_+k , ...
// so res = \sum_{d|n} euler(n/d) * f(d).
// below is direct from above. but a linear sweep could do.
void solve() {
    int n; cin >> n;
    vector<bool> a(n);
    bool zero = 0;
    bool tot = 0;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        a[i] = c=='1';
        zero |= a[i];
        tot ^= a[i];
    }
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
    sieve();
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
        if (x==1) return vector<int>(1, 1);
        //assert(x > 1);
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
    auto eu = [&](int x) {
        if (x==1) return 1;
        int res = x;
        for (auto& p: decomp(x)) {
            res /= p.first;
            res *= (p.first - 1);
        }
        return res;
    };
    auto f = [&](int x) {
        assert(x > 0);
        assert(n%x==0);
        vector<bool> perm(n, false);
        for (int i = 0; i < n; i++) {
            if (!perm[i]) {
                perm[i] = true;
                bool flag = a[i];
                for (int j = (i+x)%n; j != i; j+=x, j%=n) {
                    flag ^= a[j];
                    perm[j] = true;
                }
                if (flag) return 0;
            }
        }
        return 1;
    };
    int res = !zero;
    for (int d: divs(n)) {
        if (d==n) continue;
        res += eu(n/d) * f(d);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
