#include <bits/stdc++.h>

using namespace std;

const int MOD =  998244353; // 998244853;

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

struct Dsu {
    int n;
    vector<int> p;
    vector<int> d; // parity of total deg
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
        d.assign(n, 0);
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        d[x] ^= d[y];
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline void flip(int x) {
        d[find(x)] ^= 1;
    }
    inline int get(int x) {
        return d[find(x)];
    }
};

const int N = 1503;
const int OFF = 1, ON = 2, ANY = 0, NOPE = -1; 
int state[N][N];

// let [0,.., n] be coord/id of rectangle
// each op/grid view as edge of graph of rects.
// base op: we can flip a trangle
//   if N even => base op: we can flip any edge
//   odd => we can flip euler-cycle => any-deg should be even
//      then for scc of ANY edges, let T be some MST, then if (G-T) fixed, from leaf we can determine T.
//      as long as d(G) == 0, since each choose don't alter parity
void solve() {
    int n; cin >> n;
    bool consistent = true;
    for (int i = 1; i < n; i++) {
        string s; cin >> s;
        for (int j = 1; j < n; j++) {
            int v = ANY;
            if (s[j-1] == 'o') v = ON;
            else if (s[j-1] == 'x') v = OFF;
            // trans coord
            int x = abs(i-j); // reflex at 0
            int y = i+j;
            if (y > n) y = 2*n - y; // reflex at n
            if (x > y) swap(x, y);
            //cout << x << ' '<< y << ',';

            if (v == ANY) continue;
            if (state[x][y] == ANY) {
                state[x][y] = v;
            } else if (state[x][y] != v) {
                state[x][y] = NOPE;
                consistent = false;
                //cout << 0; return;
            }
        }//cout << "\n";
    }
    if (!consistent) {
        cout << 0; return;
    }

    mint res = 1;
    // two indep graph, since only parity-same rect valid op
    for (int _ = 0; _ < 2; _++) {
        Dsu d(n+1);
        int tot = 0;
        int cnt = 0; // free edge
        for (int i = _; i <= n; i+=2) {
            for (int j = i+2; j <= n; j+=2) {
                int& s = state[i][j];
                //cout << s << ' ';
                if (s == ANY) {
                    tot++;
                    cnt += !d.join(i, j);
                } else if (s == ON) {
                    d.flip(i);
                    d.flip(j);
                }
            }//cout << '\n';
        }
        int N = _? (n+1)/2 : 1 + n/2;
        if (N % 2 == 0) {
            res *= mint(2).exp(tot);
        } else {
            for (int i = _; i <= n; i+=2) {
                if (d.get(i)) {
                    cout << 0; return;
                }
            }
            res *= mint(2).exp(cnt);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
