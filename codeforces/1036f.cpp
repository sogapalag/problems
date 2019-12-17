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
    // prime divisors
    vector<int> p_divs(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        vector<int> res;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
            if (x % p == 0) {
                while (x % p == 0) {
                    x /= p;
                }
                res.emplace_back(p);
            }
        }
        if (x != 1)
            res.emplace_back(x);
        return res;
    }
    // Hint: if query many times, a slight fast formula by mobius: res = sum_{d|c} mu[d] * (m/d)
    // count [1..=m] coprime to c
    int coprime(int m, int c){
        int tmp = 0;
        auto di = p_divs(c);
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
    // euler phi, [1..=x] coprime to x
    int phi(int x) {
        assert(x > 0);
        if (x == 1) return 1;
        int res = x;
        for (auto& p: p_divs(x)) {
            (res/=p)*=(p-1);
        }
        return res;
    }
    // pre-comp phi table
    vector<int> phi_table(int n) {
        assert(sz >= n);
        vector<int> res(n+1);
        iota(res.begin(), res.end(), 0);
        for (const int& p: prime) {
            if (p > n) break;
            --res[p];
            for (int i = 2*p; i <= n; i += p)
                (res[i]/=p)*=p-1;
        }
        return res;
    }
    // mobius, (-1)^k; 0, p^2|x
    int8_t mu(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        if (x == 1) return 1;
        int cnt = 0;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
            if (x % p == 0) {
                cnt++; x /= p;
            }
            if (x % p == 0) {
                return 0;
            }
        }
        if (x != 1) cnt++;
        return (cnt&1)?-1:1;
    }
    // pre-comp mobius table
    vector<int8_t> mobius_table(int n) {
        assert(sz >= n);
        vector<int8_t> res(n+1, 1);
        for (int i = 2; i <= n; i++) {
            if (is[i]) res[i] = -1;
            for (const int& p: prime) {
                if (p > i || (int64_t)p*i > n) break;
                if (i % p == 0) {
                    res[i*p] = 0;
                } else {
                    res[i*p] = -res[i];
                }
            }
        }
        return res;
    }
};
vector<int8_t> mu = Sieve(1000).mobius_table(1000);

const long long INF = 0x3f3f3f3f3f3f3f3f;

template <typename T>
T mpow(T x, int64_t e) {
    T res = 1;
    for (; e; e >>= 1) {
        if (e & 1) { if (res<INF/x)res *= x;else return INF;}
        if (x<INF/x)x *= x;else x=INF;
    }
    return res;
}

//void solve() {
//    ll n; cin >> n;
//    vector<ll> a;
//    a.push_back(n-1);
//    for (int i = 2; (1ll<<i) <= n; i++) {
//        long double x = pow((long double)n, (long double)1/i);
//        ll m = x;
//        while (mpow<ll>(m, i) <= n) {
//            m++;
//        }
//        while (mpow<ll>(m, i) > n) m--;
//        //cout << m << "\n";
//        assert(m>1);
//        a.push_back(m-1);
//    }
//    ll res = 0;
//    for (int i = 0; i < (int)a.size(); i++) {
//        res += mu[i+1] * a[i];
//    }
//    cout << res << "\n";
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    int t; cin >> t;
//    while(t--)solve();
//    cout << endl;
//}

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

ll ub[66];

// d|g, m^d <=n.  to 1|gcd(e(m)) problem, m-1
// offline, Caution: pow, sqrt
void solve() {
    int q; cin >> q;
    vector<pair<ll, int>> qs(q);
    for (int i = 0; i < q; i++) {
        ll n; cin >> n;
        qs[i] = {n,i};
    }
    sort(qs.begin(), qs.end(), greater<pair<ll,int>>());
    
    ub[3] = 1e6;
    ub[4] = 31622;
    ub[5] = 3981;
    for (int e = 6; e < 9; e++) {
        ub[e] = 1000;
    }
    for (int e = 9; e < 18; e++) {
        ub[e] = 100;
    }
    for (int e = 18; e < 66; e++) {
        ub[e] = 10;
    }

    auto _sqrt = [](ll n){
        return bs_last<ll>(1, 1e9+2, [&](ll x){return x*x<=n;});
    };

    auto calc = [&](ll n){
        ll res = n-1; res += mu[2] * (_sqrt(n)-1);
        for (int e = 3; (1ll<<e) <= n; e++) {
            while (mpow(ub[e], e) > n) {
                ub[e]--;
            }
            res += mu[e] * (ub[e]-1);
        }
        return res;
    };
    vector<ll> res(q);
    for (int _ = 0; _ < q; _++) {
        ll n;int i;
        tie(n,i) = qs[_];
        res[i] = calc(n);
    }
    for (auto& x: res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
