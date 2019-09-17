#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

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
    // euler phi, [1..=x] coprime to x
    ll phi(ll x) {
        assert(x > 0);
        if (x == 1) return 1;
        int res = x;
        for (auto& p: p_divs(x)) {
            (res/=p)*=(p-1);
        }
        return res;
    }

} s(1e6);

template <typename T>
T mpow(T x, int64_t e, ll mod) {
    T res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res *= x, res %= mod;
        x *= x, x %= mod;
    }
    return res;
}

ll a;
ll calc(ll m) {
    if (m == 1) return 1;
    ll p = s.phi(m);
    ll l = m*p/__gcd(p,m);
    ll y = calc(p);
    return l + mpow<__int128>(a, y, l);
}

// editorial method: get y=calc(gcd(m,p)), then use ex-crt find x = A^y (%m), x = y (%p). x is ans.
//    since A^x = A^y (euler, %p) 
// here method: get y = calc(p). then we get x=A^y (%mp/g) imply under (%m) (%p) both equal.
//    so A^x = A^y = x(%m) trivially
void solve() {
    ll m;
    cin >> a >> m;
    ll y = calc(m);
    assert(mpow<__int128>(a,y,m) == y%m);
    cout << y << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
