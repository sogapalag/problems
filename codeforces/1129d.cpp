#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353; // 998244853;

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

const int N = 100005; 
mint dp[N];

int K;

const int BLOCK_SIZE = 256; 


struct Block {
    int L, R;
    // suff[i] := #single in [L+i..N]
    int suff[BLOCK_SIZE], offset, height;
    // sum[i] := ways s.t. suff <= offst+i
    mint sum[BLOCK_SIZE];
    Block() {}
    Block(int _L, int _R) : L(_L), R(_R), offset(0), height(0) {
        memset(suff, 0, sizeof suff);
        memset(sum, 0, sizeof sum);
    }

    void update(int l, int r, int x) {
        assert(L <= l && r <= R);
        if (L == l && r == R) {
            offset += x; return;
        }
        for (int i = l; i < r; i++) {
            suff[i-L] += x;
        }
        int delta = *min_element(suff, suff + BLOCK_SIZE);
        offset += delta;
        for (int i = L; i < R; i++) {
            suff[i-L] -= delta;
        }
        height = *max_element(suff, suff + BLOCK_SIZE);
        memset(sum, 0, sizeof sum);
        for (int i = L; i < R; i++) {
            sum[suff[i-L]] += dp[i];
        }
        for (int i = 1; i <= height; i++) {
            sum[i] += sum[i-1];
        }
    }

    mint query() {
        int x = K - offset;
        return x < 0 ? 0 : sum[min(x, height)];
    }

    void add(int l) {
        for (int i = suff[l-L]; i <= height; i++) {
            sum[i] += dp[l];
        }
    }
};

vector<Block> bs;
void update_all(int l, int r, int x) {
    if (l >= r) return;
    for (int i = l/BLOCK_SIZE; l < r; i++) {
        int _r = min(r, bs[i].R);
        bs[i].update(l, _r, x);
        l = _r;
    }
}
mint query_all(int r) {
    mint res = 0;
    for (auto& b: bs) {
        if (r < b.L) break;
        res += b.query();
    }
    return res;
}

// 0... ,-1, 1
void solve() {
    int n;
    cin >> n >> K;
    for (int l = 0; l <= n; l += BLOCK_SIZE) {
        bs.emplace_back(l, min(l + BLOCK_SIZE, n+1));
    }
    dp[0] = 1; bs[0].add(0);
    vector<int> pre(n+1), las(n+1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        int p = las[x]; las[x] = i; pre[i] = p;
        update_all(p, i, 1);
        int s = pre[p];
        update_all(s, p, -1);
        
        dp[i] = query_all(i);
        bs[i/BLOCK_SIZE].add(i);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
