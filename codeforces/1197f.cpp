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

const int N = 64; 
const int L = 31; 
using M = array<array<mint,N>,N>;
using V = array<mint,N>;
M mul(M& a, M& b) {
    M r = {};
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 64; k++) {
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return r;
}
V mul(V& v, M& a) {
    V r = {};
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            r[j] += v[i] * a[i][j];
        }
    }
    return r;
}

M C[3] = {};
M A = {};
M ex[L];
int g[3][3];

int gate(int i, int c) {
    bool mex[4] = {};
    for (int _ = 0; _ < 3; _++) {
        if (g[c][_]) {
            mex[(i>>(4 - 2*_))&0b11] = true;
        }
    }
    int now = 0;
    while (mex[now]) {
        now++;
    }
    return (now<<4) | (i>>2);
}
// not used, v[63]=1, is enough for init (x<3) cases.
int general_gate(int i, vector<int>& can_go) {
    bool mex[4] = {};
    for (int _:can_go){
        mex[(i>>(4 - 2*_))&0b11] = true;
    }
    int now = 0;
    while (mex[now]) {
        now++;
    }
    return (now<<4) | (i>>2);
}

void prep() {
    for (int i = 0; i < 64; i++) {
        for (int c = 0; c < 3; c++) {
            int j = gate(i,c);
            A[i][j] += 1;
            C[c][i][j] += 1;
        }
    }
    ex[0] = A;
    for (int i = 1; i < L; i++) {
        ex[i] = mul(ex[i-1], ex[i-1]); // not pw[i-1]*pw[0]
    }
}

// first for each strip calc its dp[sg], since move-length<=3, one can see sg<=3
// note g[i][j] is color i, j step, not color i, color j.(which much difficult)
// A[64][64], i.e. prev(sg[3]) -> now(sg[3]), prep for since many uncolored
void solve() {
    int n; cin >> n;
    vector<int> len(n);
    for (auto& x: len) {
        cin >> x;
    }
    int m; cin >> m;
    vector<vector<pair<int,int>>> a(n);
    for (int _ = 0; _ < m; _++) {
        int i, x, c;
        cin >> i >> x >> c;
        i--;x--;c--;
        a[i].emplace_back(x, c);
    }
    for (int i = 0; i < n; i++) {
        sort(a[i].begin(), a[i].end());
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> g[i][j];
        }
    }
    prep();

    auto advance = [&](V& v, int step){
        for (int i = L-1; i >= 0; i--) {
            if (step>>i&1) v = mul(v, ex[i]);
        }
    };
    auto step_with_color = [&](V& v, int c){
        v = mul(v, C[c]);
    };
    using R = array<mint,4>;
    auto calc = [&](vector<pair<int,int>>& strip, int n){
        V v = {}; v[63] = 1;
        int las = -1;
        for (auto& _: strip) {
            int x, c;
            tie(x, c) = _;
            if (x - las > 1) {
                advance(v, x-las-1);
            }
            step_with_color(v, c);
            las = x;
        }
        if (n - las > 1) advance(v, n-las-1);
        R r = {};
        for (int i = 0; i < 64; i++) {
            r[i>>4] += v[i];
        }
        return r;
    };

    R dp = {}; dp[0] = 1;
    for (int i = 0; i < n; i++) {
        R sg = calc(a[i], len[i]);
        //for (int k = 0; k < 4; k++) {
        //    cerr<<sg[k]<<' ';
        //}cerr<<endl;
        R nxt = {};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                nxt[i^j] += dp[i] * sg[j];
            }
        }
        swap(dp, nxt);
    }
    cout << dp[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
