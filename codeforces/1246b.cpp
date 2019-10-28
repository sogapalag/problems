#include <bits/stdc++.h>

using namespace std;

#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

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
}s(1e5+10);
using ll=long long;
const int N = 100005; 

void solve() {
    int n,K;
    cin >> n >> K;
    vector<int> cnt(N);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<int> a; a.reserve(400); // possible coeff candidate sz<400 since 400^2>1e5
    a.emplace_back(1);
    for (int i = 2; ; i++) {
        int x = 1;
        bool fail = false;
        for (int _ = 0; _ < K; _++) {
            x *= i;
            if (x >= N) {
                fail = true;
                break;
            }
        }
        if (fail) break;
        a.emplace_back(x);
    }
dbg(a);
    ll sum = 0;
    ll s2 = 0;
    for (int i = 1; i < N; i++) {
        if (cnt[i]) {
            ll com = 1;
            bool fail = false;
            for (auto& p: s.factor(i)) {
                int b,e;
                tie(b,e) = p;
                e = (K-e)%K;
                (e+=K) %= K;
                if (e >= 17) {
                    fail = true; break;
                }
                for (int _ = 0; _ < e; _++) {
                    com *= b;
                    if (com >= N) {
                        fail = true; break;
                    }
                }
                if (fail) break;
            }
dbg(i, com);
            if (!fail) {
                for (auto& x: a) {
                    ll tmp = com*x;
                    if (tmp >= N) break;
                    sum += 1ll*cnt[i] * cnt[tmp];
                    if (tmp == i) s2 += cnt[i];
                }
            }
dbg(sum);
        }
    }
dbg(sum, s2);
    ll res = (sum-s2)/2;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
