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

// n X n, for linear recurrence use
template <typename T>
struct Matrix {
    int n;
    vector<vector<T>> a;

    // Caution: default I
    constexpr Matrix(int _n=2) : n(_n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].resize(n);
        }
        set_id();
    }
    constexpr Matrix(const Matrix& _m) {
        n = _m.n;
        a = _m.a;
    }
    Matrix& operator=(const Matrix& _m) {
        n = _m.n;
        a = _m.a;
        return *this;
    }
    void set_all(const T& val) {
        for (auto& r: a) {
            for (auto& x: r) {
                x = val;
            }
        }
    }
    void set_id() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i==j? 1 : 0;
            }
        }
    }
    T trace() {
        T sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i][i];
        }
        return sum;
    }
    // sometimes use for v*A
    void transpose() {
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
    
    Matrix& operator+=(const Matrix& _m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] += _m.a[i][j];
            }
        }
        return *this;
    }
    Matrix& operator-=(const Matrix& _m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] -= _m.a[i][j];
            }
        }
        return *this;
    }
    // if impl as a = tmp*_m.a will WA when A*=A;
    Matrix& operator*=(const Matrix& _m) {
        auto r = a;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    r[i][j] += a[i][k] * _m.a[k][j];
                }
            }
        }
        a = r;
        return *this;
    }
    // r = A*v
    vector<T> operator*(const vector<T>& v) {
        assert(n == (int)v.size());
        vector<T> res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i] += a[i][j] * v[j];
            }
        }
        return res;
    }
    Matrix operator+(const Matrix& _m) {
        return Matrix(*this) += _m;
    }
    Matrix operator-(const Matrix& _m) {
        return Matrix(*this) -= _m;
    }
    Matrix operator*(const Matrix& _m) {
        return Matrix(*this) *= _m;
    }
    template <typename U>
    Matrix exp(U e) {
        assert(e >= 0);
        Matrix res(n);
        Matrix b = *this;
        for (; e; e >>= 1) {
            if (e&1) res *= b;
            b *= b;
        }
        return res;
    }
};

template <typename T, typename U>
struct Seglazy {
    static const int H = 17; //20
    static const int SZ = 1<<H;
    int sz_v;
    const T ID;  // identity
    const U UN;  // not info
    vector<T> v; // tree
    vector<U> d; // lazy
    
    Seglazy() : sz_v(SZ<<1), ID(), UN(0), v(sz_v), d(sz_v, 0) {
        //v.resize(sz_v);
        //d.resize(sz_v);
    }
    inline int len(int p) {
        return 1 << (H + __builtin_clz(p) - 31);
    }
    void build(int p=1, int l=0, int r=SZ) {
        if (l + 1 == r) {
            //set leaf
            return;
        }
        assert(l != r);
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        build(pl, l, m);
        build(pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    inline void apply(int p) {// do!! use info, may need length, pass l, r in
        //v[p] += d[p] * len(p); //.x
        if (p) {
            swap(v[p].x.a[0][0], v[p].x.a[1][1]);
            swap(v[p].x.a[0][1], v[p].x.a[1][0]);
        }
    }
    inline void store(int p, const U& val) {// do!! store info, careful!! info chain
        d[p] ^= val; // ^
    }
    inline void push(int p) {
        apply(p);
        if (p < SZ) {
            store(p<<1, d[p]);
            store(p<<1|1, d[p]);
        }
        d[p] = UN;
    }
    void update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
            store(p, val);
            push(p);
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m);
        update(_l, _r, val, pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    T query(int _l, int _r, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) { return ID; }
        if (_l <= l && r <= _r) { return v[p]; }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        return query(_l, _r, pl, l, m) + query(_l, _r, pr, m, r);
    }    
};    

struct Node {// monoid
    Matrix<mint> x;
    
    Node() : x() {} // write your own identity
    //Node(int _x) : x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) {
        //x = max(x, _r.x); // write your own  !! may not communitative
        x *= _r.x;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

using Seg=Seglazy<Node, int>;
Seg seg;

void update_all(int l, int r) {
    seg.update(l, r, 1);    
}
void query_all(int l, int r, mint x, mint y) {
    auto res = seg.query(l, r).x;
    res.transpose();
    vector<mint> v = {x, y};
    v = res * v;
    cout << v[0] << ' ' << v[1] << "\n";
}

Matrix<mint> A, B;

// after toggle, can view swap input {x,y}, output swap too.
//  <=> swap M[0][1]<->M[1][0], M[0][0]<->M[1][1]
void solve() {
A.a[1][0] = B.a[0][1] = 1;
    int n, q;
    cin >> n >> q;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        seg.v[Seg::SZ+i].x = s[i]=='A'? A : B;
    }
    seg.build();

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l,r;
            cin >> l >> r;
            l--;
            update_all(l, r);
        } else {
            int l,r,x,y;
            cin >> l >> r >> x >> y;
            l--;
            query_all(l,r,x,y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
