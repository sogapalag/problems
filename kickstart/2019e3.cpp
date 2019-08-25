#include <bits/stdc++.h>

using namespace std;

    vector<int> prime;

// x = 2^e *p^e1*..
// e=0: 1, 2, 3, 5, 7, 11,... prime
// e=1: 2(1,3,5,7,9,11,...) odd
// e=2: 4(1,2,3,5,7,11,...) prime
// careful dup.
void solve() {
    int l, r;
    cin >> l >> r;
    
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

    auto qry = [&](int R){
        if (R<=0) return 0;
        int res = (R/2 + 1)/2;
        return res;
    };
    int res = qry(r) - qry(l-1); // 2[1,3,5...]

    auto is_pr = [&](int x)->bool{
        if (x == 1) return true;
        auto d = decomp(x);
        if ((int)d.size()>1) return false;
        if (d[0].second > 1) return false;
        return true;
    };
    for (int i = l; i <= r; i++) {
        if (i==2) continue; //qry computed
        if (is_pr(i)) res++;
    }
    l = (l+3)/4, r = r/4;
    for (int i = l; i <= r; i++) {
        if (is_pr(i)) res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
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
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
