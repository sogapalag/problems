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
    vector<int64_t> p_divs(int64_t x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        vector<int64_t> res;
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
}s(2e6);

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// key, since check(2) <= n, which imply at least n/2 element with change <=1
// so random pick x (1/2 prob hit), check(x-1,x,x+1)
void solve() {
    clock_t begin = clock();
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }

    ll res = n;
    set<ll> done;
    auto check = [&](ll p){
        if (done.find(p) != done.end()) return;
        done.insert(p);
        ll tmp = 0;
        for (ll x: a) {
            if (x <= p) tmp += p-x;
            else {
                x %= p;
                tmp += min(x, p-x);
            }
        }
        res = min(res, tmp);
    };
    check(2);

    while (clock() - begin < 2020) {
        ll x = a[rng()%n];
        for (ll y: {x-1,x,x+1}){
            if (y > 1) {
                for (ll d: s.p_divs(y)) check(d);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
