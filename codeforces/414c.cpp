#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

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
using ll=long long;

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

void __solve() {
    int n; cin >> n;
    const int MSK = 1<<n; 
    vector<int> a(MSK);
    for (auto& x: a) {
        cin >> x;
    }
    // O(n^2 2^n)
    Compress<> c(a);
    for (auto& x: a) {
        x = c.get_id(x) + 1;
    }
    vector<ll> inv(n+1);
    for (int i = 0; i <= n; i++) {
        int m = (1<<i)-1;
        auto b = a;
        for (int msk = 0; msk < MSK; msk++) {
            if ((msk^m) < msk) swap(b[msk^m], b[msk]);
        }
        ll sum = 0;
        Fenwick<> f(MSK);
        for (int x: b) {
            sum += f.query(x+1, MSK);
            f.add(x, 1);
        }
        inv[i] = sum;
    }
    // [->]1 [->]2  q   -->  [<-]1 [<-]2
    //              q+1 -->  [<-]2 [<-]1
    vector<ll> dinv(n+1); // diff
    for (int i = 1; i <= n; i++) {
        dinv[i] = inv[i] - inv[i-1];
    }
dbg(inv[0], dinv);
    // note each op, influ all subtree-depth-len(i), i.e. suff-mask
    int q; cin >> q;
    int msk = 0;
    while (q--) {
        int i; cin >> i;
        int m = (1<<i)-1;
        msk ^= m;
        ll res = inv[0];
        for (int i = 0; i < n; i++) {
            if (msk>>i&1) res += dinv[i+1];
        }
        cout << res << "\n";
    }
}

void solve() {
    int n; cin >> n;
    const int MSK = 1<<n; 
    vector<int> a(MSK);
    for (auto& x: a) {
        cin >> x;
    }

    // O(n 2^n) merge sort
    vector<ll> dinv(n+1);
    ll base = 0;
    function<void(int,int)> divi = [&](int l, int r){
        if (r-l<=1) return;
        int m = (l+r)>>1;
        divi(l,m); divi(m,r);
        int h = __builtin_ctz(r-l);
        for (int i = l, j = m; i < m; i++) {
            while (j < r && a[j] < a[i]) {
                j++;
            }
            dinv[h] += j-m;
            base += j-m; // here
        }
dbg(l,r,dinv[h], base);
        // base += dinv[h]; would cumed by different-u-same-layer, WA
        for (int i = m, j = l; i < r; i++) {
            while (j < m && a[j] < a[i]) {
                j++;
            }
            dinv[h] -= j-l;
        }
        inplace_merge(a.begin()+l, a.begin()+m, a.begin()+r);
    };
    divi(0, MSK);
dbg(base, dinv);
    int q; cin >> q;
    int msk = 0;
    while (q--) {
        int i; cin >> i;
        int m = (1<<i)-1;
        msk ^= m;
        ll res = base;
        for (int i = 0; i < n; i++) {
            if (msk>>i&1) res -= dinv[i+1]; // -
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
