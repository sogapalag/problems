#include <bits/stdc++.h>

using namespace std;

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
}s(2e5+10);
const int N = 2e5+10; 
int a[N][2];
int cnt[N];
// for some prime, let x = second-least of (e_n).
// res:= prod p^x
void solve() {
    memset(a, 0x3f, sizeof a);
    int n; cin >> n;
    fill(cnt, cnt+N, n);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        for (auto [p,e]: s.factor(x)) {
            --cnt[p];
            if (a[p][1] > e) a[p][1] = e;
            if (a[p][0] > a[p][1]) swap(a[p][0], a[p][1]);
        }
    }
    int64_t res = 1;
    for (int p = 2; p < N; p++) {
        if (s.is[p] && cnt[p] < 2) {
            if (cnt[p] == 0) {
                while (a[p][1]--) res *= p;
            } else {
                while (a[p][0]--) res *= p;
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
