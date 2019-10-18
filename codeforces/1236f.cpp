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
using ll=long long;

#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
string to_string(const mint x) {return to_string((int)x); }
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


// #scc = V(#nodes) - E(#edges) + C(#cycles)
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n, 0);
    vector<int> pa(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;
        deg[y]++;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    int cyc_cnt = 0;
    // maintain each cycle sz, foot.
    // foot: edge connect to cycle,(not in)
    vector<int> sz, foot; sz.reserve(n); foot.reserve(n);
    vector<vector<int>> cs(n);
    vector<int> sta(n, 0); int tim = 1; // use start time, in case of dup.
    function<void(int,int)> dfs = [&](int u,int p){
        sta[u] = tim++;
        for (int v: g[u]) if(v!=p){
            if (!sta[v]) {
                pa[v] = u;
                dfs(v, u);
            } else if (sta[v] < sta[u]){
                int sz_cnt = 0;
                int foot_cnt = 0;
                int x = u;
                while (x != v) {
                    sz_cnt++;
                    foot_cnt += deg[x];
                    cs[x].emplace_back(cyc_cnt);
                    x = pa[x];
                }
                sz_cnt++;
                foot_cnt += deg[v];
                cs[v].emplace_back(cyc_cnt);
                foot_cnt -= sz_cnt<<1;

                sz.emplace_back(sz_cnt);
                foot.emplace_back(foot_cnt);
                cyc_cnt++;
            }
        }
    };
    dfs(0, -1);

dbg(cyc_cnt, sz, foot);
dbg(cs);
    mint half = mint(1)/2;
    vector<mint> pw(2*n+1);
    pw[0] = 1;
    for (int i = 1; i <= 2*n; i++) {
        pw[i] = pw[i-1]*half;
    }

    mint V = n * pw[1];
    mint E = m * pw[2];
    mint C = 0;
    {
        for (auto& x: sz) {
            C += pw[x];
        }
    }

    mint V2 = n*pw[2] + V*V; // recall binomial dist.
    mint E2 = 0;
    {
        ll cnt = 0;
        for (auto& x: deg) {
            cnt += 1ll*x*(x-1);
        }
        E2 += cnt * pw[3];  //  share one end
        E2 += m * pw[2];    //  same edge
        E2 += (1ll*m*m-m-cnt) * pw[4]; // share no end
    }
    // for same cycle 2^x
    // for adj cycle with sz x,y contribute  2^(x+y-1)
    // other pair 2^(x+y)
    mint C2 = 0;
    {
        mint adj = 0;
        for (int i = 0; i < n; i++) {
            if (cs[i].size() < 2) continue;
            mint tmp = 0;
            mint t2 = 0;
            for (int j: cs[i]) {
                int x = sz[j];
                tmp += pw[x];
                t2 += pw[x] * pw[x];
            }
            adj += tmp*tmp - t2;
        }
        mint sum = C*C;
        mint s2 = 0;
        for (auto& x: sz) {
            s2 += pw[x]*pw[x];
        }
        C2 += adj * 2;
        C2 += C;
        C2 += (sum-s2-adj);
    }

    // consider node whether in each edge
    mint VE = m * (2*pw[2] + (n-2)*pw[3]);
    // consider node whether in each cycle
    mint VC = 0;
    {
        for (auto& x: sz) {
            VC += x * pw[x];
            VC += (n-x) * pw[x+1];
        }
    }
    // consider edge type: in, foot, other
    mint EC = 0;
    {
        for (int i = 0; i < cyc_cnt; i++) {
            int x = sz[i], y = foot[i];
            EC += x * pw[x];
            EC += y * pw[x+1];
            EC += (m-x-y) * pw[x+2];
        }
    }

dbg(V,E,C);
dbg(V2,E2,C2);
dbg(VE,VC,EC);
    mint X = V-E+C;
    mint res = V2+E2+C2 -2*VE + 2*VC - 2*EC - X*X;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
