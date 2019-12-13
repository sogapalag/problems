#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct Sieve {
    int sz;
    vector<bool> is;
    vector<int> prime;
    Sieve(int n = 45000):sz(n) {
        prime.reserve(n/6);
        is.assign(n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; (int64_t)p*p <= n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    }
    // x=p0^e0 * p1^e1 *...
    vector<pair<int, int>> factor(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        vector<pair<int, int>> res;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
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
    }
    // divisors
    vector<int> divs(int x, bool sorted=false) {
        vector<int> res;
        res.emplace_back(1);
        for (auto& p: factor(x)) {
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
        if (sorted) sort(res.begin(), res.end());
        return res;
    }
    // number of divisors
    int num_divs(int x) {
        int res = 1;
        for (auto& pe: factor(x)) {
            res *= (1+pe.second);
        }
        return res;
    }
};
const int N = 100005; 
const int n = 3; 

vector<int> perm[6];
int cnt_divs[N];

void prep() {
    vector<int> p = {0,1,2};
    int i = 0;
    do {
        perm[i++] = p;
    } while(next_permutation(p.begin(), p.end()));

    Sieve s(N);
    for (int i = 1; i < N; i++) {
        cnt_divs[i] = s.num_divs(i);
    }
}
const int MSK = 1<<6; 
int a[3] , x[3], g[8];
ll f[MSK];
// MSK rep (x,y,z) sat which oritations.
// note the naive algo is count tuple (x,y,z)
// so for 3-differ, 2-equal, all-same. counted 6, 3, 1 times
// so we add du*3, where du is count (x=y,z)
// now, (6,6,4). since y=z also counted
// finally add 2* #(x=y=z) to have (6,6,6) to divide 6, get the answer
void solve() {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < 8; i++) {
        int _g = 0;
        for (int j = 0; j < 3; j++) {
            if (i>>j&1)_g = __gcd(_g, a[j]);
        }
        g[i] = cnt_divs[_g];
    }
    ll dual = 0;
    for (int msk = 1; msk < MSK; msk++) {
        memset(x, 0, sizeof x);
        for (int i = 0; i < 6; i++) {
            if (msk>>i&1) {
                for (int k = 0; k < 3; k++) {
                    x[k] |= 1 << perm[i][k];
                }
            }
        }
        f[msk] = 1ll;
        for (int i = 0; i < 3; i++) {
            f[msk] *= g[x[i]];
        }
        ll du = 1ll * g[x[0]|x[1]] * g[x[2]];
        dual += (__builtin_popcount(msk)&1) ? du : -du;
        //cerr<<msk<<','<<f[msk]<<endl;
    }
    ll res = 0;
    for (int msk = 1; msk < MSK; msk++) {
        res += (__builtin_popcount(msk)&1) ? f[msk] : -f[msk];
    }
    res += dual * 3;
    res += g[7] * 2;
    res /= 6;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int t;cin >> t;
    while(t--)solve();
    cout << endl;
}
