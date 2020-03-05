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

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

/* draft, forgot consider mid index would change.
void solve() {
    int n; cin >> n;
    vector<int> Xs;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        Xs.push_back(x);
    }
    int q; cin >> q;
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; i++) {
        int x,y;
        cin >> x >> y;
        x--;
        qs[i] = {x,y};
        Xs.push_back(y);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    Fenwick<mint> pref(Xs.size()), suff(Xs.size());
    Fenwick<int> kth(Xs.size());

    vector<mint> pw(n + 1), ipw(n + 1);
    {
        pw[0] = ipw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i-1] * 2;
        }
        ipw[1] = mint(1)/2;
        for (int i = 2; i <= n; i++) {
            ipw[i] = ipw[i-1] * ipw[1];
        }
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    auto pos = [&](int x){
        x = lower_bound(Xs.begin(), Xs.end()) - Xs.begin();
        return x + 1;
    };
    mint res = 0;
    for (int _ = 0; _ < n; _++) {
        int i = id[_];
        int k = _ + 1;
        int x = a[i];
        mint val = x;
        x = pos(x);
        res += pref.query(x) * val * ipw[k];
        pref.add(x, val * pw[k]);
        kth.add(x, 1);
        suff.add(x, val * ipw[k]);
    }

    auto del = [&](int i){
        int x = a[i];
        mint val = x;
        x = pos(x);
        int k = kth.query(x); kth.add(x, -1);
        pref.add(x, -val * pw[k]);
        res -= pref.query(x) * val * ipw[k];
        res -= suff.query(x+1, Xs.size()) * val * pw[k];
        suff.add(x, -val * ipw[k]);
    };
    // k -> k, mid changed...
    auto add = [&](int i, int x){
        a[i] = x;
        mint val = x;
        x = pos(x);
        kth.add(x, 1);
        int k = kth.query(x);
        res += pref.query(x) * val * ipw[k];
        pref.add(x, val * pw[k]);
        suff.add(x, val * ipw[k]);
        res += suff.query(x+1, Xs.size()) * val * pw[k];
    };
    for (auto& _: qs) {
        int i,x;
        tie(i,x) = qs[_];
        del(i);
        add(i, x);
    }

}
*/

template <typename M>
struct SegTree {
    using Op = function<M(const M&, const M&)>;
    M ID; // monoid identity
    Op op; // associative operation
    int N; // 2^lg space, for non-commutative
    vector<M> a;
    
    SegTree(int n, M leaf_default, M _ID, Op _op) : ID(_ID), op(_op) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegTree(const vector<M> leaves, M _ID, Op _op) : ID(_ID), op(_op) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N<<=1;
        a.assign(N<<1, ID);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }

    void assign(int p, M val) {
        assert(0 <= p && p < N);
        for (a[p += N] = val; p >>= 1;) pull(p);
    }
    M query(int l, int r) const {
        assert(0 <= l && r <= N);
        M resl(ID), resr(ID);
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = op(resl, a[l++]);
            if (r & 1) resr = op(a[--r], resr);
        }
        return op(resl, resr);
    }
    M query_point(int p) const { 
        assert(0 <= p && p < N);
        return a[p + N];
    }
    M query_all() const { return a[1]; }
};
using pi=pair<int,int>;
// consider pair in sorted, ai*aj, i.e. i,j chosen, between must not, i.e. 2^-{j-i+1} prob 
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<pi> Xs; // pair, break tie
    for (auto& x: a) {
        cin >> x;
    }
    for (int i = 0; i < n; i++) {
        Xs.emplace_back(a[i], i);
    }
    int q; cin >> q;
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; i++) {
        int x,y;
        cin >> x >> y;
        x--;
        qs[i] = {x,y};
        Xs.emplace_back(y, x);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    int m = Xs.size();

    vector<mint> pw(n + 1), ipw(n + 1);
    {
        pw[0] = ipw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i-1] * 2;
        }
        ipw[1] = mint(1)/2;
        for (int i = 2; i <= n; i++) {
            ipw[i] = ipw[i-1] * ipw[1];
        }
    }
    auto pos = [&](pi p){
        return lower_bound(Xs.begin(), Xs.end(), p) - Xs.begin();
    };

    struct M {
        mint sum, l, r;
        int k;
        M() {sum=l=r=0,k=0;}
        M(mint _sum, mint _l, mint _r, int _k) : sum(_sum), l(_l), r(_r), k(_k) {}
    };
    vector<M> leaves(m);
    for (int i = 0; i < n; i++) {
        int p = pos({a[i],i});
        mint x = a[i];
        leaves[p] = {0, x*2, x*ipw[1], 1};
    }

    SegTree<M> s(leaves, {0,0,0,0}, [&](M u, M v){
            M r;
            r.sum = u.sum + v.sum + u.l * (v.r * ipw[u.k]);
            r.l = u.l + v.l * pw[u.k];
            r.r = u.r + v.r * ipw[u.k];
            r.k = u.k + v.k;
            return r;
            });
    
    mint res = s.query_all().sum * ipw[1];
    cout << res << "\n";
    for (auto& _: qs) {
        int i,x;
        tie(i,x) = _;
        int p = pos({a[i], i});
        s.assign(p, {});

        p = pos({a[i]=x, i});
        mint val = x;
        s.assign(p, {0, val*2, val*ipw[1], 1});
        mint res = s.query_all().sum * ipw[1];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
