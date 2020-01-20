#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353;  998244853; 

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
#define dbg(args...) 2020
#endif

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> formula(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        formula[i] = {x,y};
    }
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<bool> trk(n);
    {
        // rev graph
        vector<vector<int>> rg(n);
        for (int i = 0; i < n; i++) {
            int x,y;
            tie(x,y) = formula[i];
            rg[x].push_back(i);
            rg[y].push_back(i);
        }
        // mark x -> 0
        queue<int> q;
        q.push(0); trk[0] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: rg[u])if(!trk[v]){
                q.push(v); trk[v] = true;
            }
        }
    }
    vector<bool> vis(n);
    {
        // mark a>0 -> x
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) if(trk[i]){
            int x,y;
            tie(x,y)=formula[i];
            if (trk[x]) g[i].push_back(x);
            if (trk[y]) g[i].push_back(y);
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                q.push(i); vis[i] = true;
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: g[u])if(!vis[v]){
                q.push(v); vis[v] = true;
            }
        }
    }
    // useful/matter
    {// note the remain graph each vertex can always ->0
        vector<vector<int>> g(n);
        vector<int> indeg(n), outdeg(n);
        vector<mint> cnt(n);
        for (int i = 0; i < n; i++) if(trk[i]&&vis[i]){
dbg(i);
            cnt[i] = a[i];
            int x,y;
            tie(x,y)=formula[i];
            if (trk[x]&&vis[x]) g[i].push_back(x),outdeg[i]++,indeg[x]++;
            if (trk[y]&&vis[y]) g[i].push_back(y),outdeg[i]++,indeg[y]++;
        }
dbg(g);
        queue<int> q;
        for (int i = 0; i < n; i++)if(trk[i]&&vis[i]) {
            if (indeg[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == 0) continue; // isolated case
            // u -> v..
            mint x = cnt[u]; cnt[u] = 0;
            for (int v: g[u]){
                outdeg[u]--; indeg[v]--;
                cnt[v] += x;
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }
        mint res = 0;
        // remain cycle? two branch
        for (int i = 0; i < n; i++) {
            if (outdeg[i] == 2) {
                cout << "UNBOUNDED\n";return;
            }
            res += cnt[i]; // any u -> 0 at most 1
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
