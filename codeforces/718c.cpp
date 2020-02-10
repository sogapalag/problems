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

template <typename M, typename D>
struct SegLazy {
    using Op = function<M(const M&, const M&)>;
    using D2M = function<void(M&, const D&)>;
    using D2D = function<void(D&, const D&)>;
    
    M ID;
    D UN;
    Op op;
    D2M d2m;
    D2D d2d;

    int N, L;
    vector<M> a; // tree
    vector<D> d; // lazy
    
    SegLazy(int n, M leaf_default, M _ID, D _UN, Op _op, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op), d2m(_d2m), d2d(_d2d)
    {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegLazy(const vector<M>& leaves, M _ID, D _UN, Op _op, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op), d2m(_d2m), d2d(_d2d)
    {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; L = 0; while (N < n) N <<= 1, L++;
        a.assign(N<<1, ID);
        d.assign(N, UN);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }
    inline int len(int i) {
        return 1 << (L + __builtin_clz(i) - 31);
    }
    inline void apply(int i, const D& dval) {
        d2m(a[i], dval);
        if (i < N) d2d(d[i], dval);
    }
    inline void push(int i) {
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = UN;
    }
    void update(int l, int r, const D& dval, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        if (l <= sl && sr <= r) return apply(i, dval);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        update(l, r, dval, il, sl, sm);
        update(l, r, dval, ir, sm, sr);
        pull(i);
    }
    M query(int l, int r, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return ID;
        if (l <= sl && sr <= r) return a[i];
        push(i);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        return op(query(l, r, il, sl, sm), query(l, r, ir, sm, sr));
    }

    void update(int l, int r, const D& dval) { 
        assert(0 <= l && r <= N);
        update(l, r, dval, 1, 0, N);
    }
    void assign(int p, const M& x) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        for (a[p] = x; p >>= 1; ) pull(p);

    }
    M query(int l, int r) {
        assert(0 <= l && r <= N);
        return query(l, r, 1, 0, N);
    }
    M query_point(int p) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        return a[p];
    }
    M query_all() const { return a[1]; }
};
using M = array<array<mint,2>,2>;
using ll=long long;
// (A^e1 + A^e2 + ...) * A^e = .....
// i.e. hold (.+.)*.=(.*. + .*.) Distributivity property
void __solve() {
    M ID; ID[0][0]=ID[1][1] = 1;
    auto mul = [](M u, M v){
        M r;
        for (int i:{0,1})
            for (int j:{0,1})
                for (int k:{0,1})
                    r[i][j] += u[i][k] * v[k][j];
        return r;
    };
    auto add = [](M u, M v){
        M r;
        for (int i:{0,1})
            for (int j:{0,1})
                r[i][j] = u[i][j] + v[i][j];
        return r;
    };
    M FIB; FIB[0][0]=FIB[0][1]=FIB[1][0]=1;
    auto mpow = [&](M a, ll e){
        M r = ID;
        for (; e; e >>= 1) {
            if (e & 1) r = mul(r,a);
            a = mul(a,a);
        }
        return r;
    };
    int n,q;
    cin >> n >> q;
    vector<M> a(n);
    for (int i = 0; i < n; i++) {
        int e; cin >> e;
        a[i] = mpow(FIB, e);
    }

    SegLazy<M,ll> s (a, M{}, 0,
            add,
            [&](M& u, ll e){ u = mul(mpow(FIB, e), u); },
            [](ll& e, ll x){ e+=x; }
            );

    while (q--) {
        int op,l,r;
        cin >> op >> l >> r;l--;
        if (op == 1) {
            int x; cin >> x;
            s.update(l, r, x);
        } else {
            auto u = s.query(l, r);
            cout << u[1][0] << '\n';
        }
    }
}
// replace M by V, fitin TLE
using V=array<mint,2>;
void solve() {
    M ID; ID[0][0]=ID[1][1] = 1;
    auto mul = [](M u, M v){
        M r;
        for (int i:{0,1})
            for (int j:{0,1})
                for (int k:{0,1})
                    r[i][j] += u[i][k] * v[k][j];
        return r;
    };
    auto add_V = [](V u, V v){
        return V{u[0]+v[0], u[1]+v[1]};
    };
    M FIB; FIB[0][0]=FIB[0][1]=FIB[1][0]=1;
    vector<M> fib(62);
    {
        fib[0] = FIB;
        for (int i = 1; i < 62; i++) {
            fib[i] = mul(fib[i-1], fib[i-1]);
        }
    }
    auto mul_V = [](const M& m, V v){
        return V{m[0][0]*v[0]+m[0][1]*v[1],
                 m[1][0]*v[0]+m[1][1]*v[1]};
    };
    auto pow_V = [&](V u, ll e){
        for (int i = 61; i >= 0; i--) {
            if (e>>i&1) {
                u = mul_V(fib[i], u);
            }
        }
        return u;
    };
    //auto mpow = [&](M a, ll e){
    //    M r = ID;
    //    for (; e; e >>= 1) {
    //        if (e & 1) r = mul(r,a);
    //        a = mul(a,a);
    //    }
    //    return r;
    //};
    int n,q;
    cin >> n >> q;
    vector<V> a(n);
    V Z; Z[0]=1;
    for (int i = 0; i < n; i++) {
        int e; cin >> e;
        a[i] = pow_V(Z, e);
    }

    SegLazy<V,ll> s (a, V{}, 0,
            add_V,
            [&](V& u, ll e){ u = pow_V(u, e); },
            [](ll& e, ll x){ e+=x; }
            );

    while (q--) {
        int op,l,r;
        cin >> op >> l >> r;l--;
        if (op == 1) {
            int x; cin >> x;
            s.update(l, r, x);
        } else {
            auto u = s.query(l, r);
            cout << u[1] << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
