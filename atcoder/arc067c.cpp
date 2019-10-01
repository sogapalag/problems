#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353; // 998244853;

template <typename T>
struct modular {
    constexpr modular() : val(0){}
    constexpr modular(const modular<T>& _m) : val(_m.val) {}
    template <typename U> constexpr modular(const U& _r = U()) {
        val = -MOD <= _r && _r < MOD ? _r: _r % MOD;
        if (val < 0) { val += MOD; } }
    const T operator()() { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }
    modular<T>& operator+=(const modular<T>& _m) { if ((val += _m.val) >= MOD) { val -= MOD; } return *this; }
    modular<T>& operator-=(const modular<T>& _m) { if ((val -= _m.val) < 0) { val += MOD; } return *this; }
    modular<T>& operator*=(const modular<T>& _m) { val = modular<T>(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val; return *this; }
    modular<T>& operator/=(const modular<T>& _m) {
        T a = _m.val, b = MOD, u = 0, v = 1;
        while (a != 0) {
            T q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        } return *this *= u; }
    modular<T>& operator =(const modular<T>& _m) { val = _m.val; return *this; }
    template <typename U> modular<T>& operator+=(const U& _r) { return *this += modular<T>(_r); }
    template <typename U> modular<T>& operator-=(const U& _r) { return *this -= modular<T>(_r); }
    template <typename U> modular<T>& operator*=(const U& _r) { return *this *= modular<T>(_r); }
    template <typename U> modular<T>& operator/=(const U& _r) { return *this /= modular<T>(_r); } 
    template <typename U> modular<T>& operator =(const U& _r) { val = modular<T>(_r).val; return *this; }
    modular<T> operator-() { return modular<T>(-val); }    
    template <typename U> friend bool operator==(const modular<U>&, const modular<U>&);
    friend std::istream& operator>>(std::istream& os, modular<T>& _m) { os >> _m.val; _m *= 1; return os; }
    friend std::ostream& operator<<(std::ostream& os, const modular<T>& _m) { return os << _m.val; }
    template <typename U>
    modular<T> exp(U e) {
        modular<T> res = 1;
        modular<T> b = val;
        if (e < 0) { b = 1/b; e *= -1; }
        for (; e; e >>= 1) {
            if (e & 1) { res *= b; }
            b *= b;
        } return res; }
private:
    T val;
};
template <typename T> inline modular<T> operator+(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T> inline modular<T> operator-(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T> inline modular<T> operator*(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T> inline modular<T> operator/(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T> inline bool operator==(const modular<T>& _lhs, const modular<T>& _rhs) { return _lhs.val == _rhs.val; }
template <typename T, typename U> inline bool operator==(const modular<T>& _lhs, const U& _rhs) { return _lhs == modular<T>(_rhs); }
template <typename T, typename U> inline bool operator==(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) == _rhs; }
template <typename T> inline bool operator!=(const modular<T>& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const modular<T>& _lhs, const U& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const U& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
typedef modular<int> mint;
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
}s(1024);
void solve() {
    int n; cin >> n;
    map<int, int> cnt;
    for (int i = 2; i <= n; i++) {
        for (auto& p: s.factor(i)) {
            cnt[p.first] += p.second;
        }
    }
    mint res = 1;
    for (auto& p: cnt) {
        res *= p.second + 1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
