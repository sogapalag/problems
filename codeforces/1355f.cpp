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
    // simple prime test
    bool is_prime(int x) {
        if (x <= sz) return is[x];
        return factor(x)[0].first == x;
    }
}s(1e5);
const ll LIM = 1e18; 
ll qs[22];
vector<ll> ps[22];
void test() {
    for (int i = 0, j = 0; i < 18; i++) {
        ll r = 1;
        while (r <= LIM / s.prime[j]) {
            ps[i].push_back(s.prime[j]);
            r *= s.prime[j++];
        }
        qs[i] = r;
        //cerr << r << ' ' << j << ' ' << s.prime[j] << endl;
    }
}
const ll N = 1e9;
// query 17 least qs, can know which p|X
// since larger prime >= 683.  under X<=N, 683^4>N, we know, possible error *=(e+1)=4,
// thus we just output *=2, fitin approx.
// and since #p <= 9, we use at most 5 queries to find small prime's e.
// just pair two, since N*N = LIM
// p^3 ~ 1e9, note x=1,2,3. p^3<=1e9/x. so need output 8. thus |-|<=7 
void solve() {
    vector<ll> a;
    for (int i = 0; i < 17; i++) {
        cout << "? " << qs[i] << endl;
        ll g; cin >> g;
        for (ll p:ps[i]) if(g%p==0) a.push_back(p);
    }
    assert(a.size() <= 9);
    auto f = [&](){
        if (a.empty()) return 1ll;
        ll p = a.back(); a.pop_back();
        ll x = p;
        while (x*p <= N) {
            x *= p;
        }
        return x;
    };
    ll res = 1;
    while (a.size()) {
        ll x = f()*f();
        cout << "? " << x << endl;
        cin >> x;
        res *= x;
    }
    res = s.num_divs(res);
    res = res <= 2 ? 8 : res*2; // p1p2p3
    //res = res == 1? 8 : s.num_divs(res) * 2;
    cout << "! " << res << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    test();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
