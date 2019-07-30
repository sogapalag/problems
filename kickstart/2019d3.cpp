#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
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

struct Node {
    int x, c;
    int i, j;
    Node(){}
    Node(int _x, int _c, int _i, int _j) : x(_x), c(_c), i(_i), j(_j) {}
};

// the problem is take k+1, then left/right cost c-+x
// so preprocess pref/suf min(k/2-sum)
void solve() {
    int K, n;
    cin >> K >> n;
    K++;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].c;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.c-u.x < v.c - v.x; 
            });
    for (int i = 0; i < n; i++) {
        a[i].i = i+1;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.c+u.x < v.c+v.x;
            });
    for (int i = 0; i < n; i++) {
        a[i].j = i+1;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.x < v.x;
            });
    int h = K/2;
    Fenwick<ll> sum(n);
    Fenwick<int> st(n);
    vector<ll> pref(n, 1ll<<61);
    for (int i = 0; i < h; i++) {
        st.add(a[i].i, 1);
        sum.add(a[i].i, a[i].c-a[i].x);
    }
    for (int i = h; i < n; i++) {
        int pos = bs_first<int>(1, n+1, [&](int _p){
                return st.query(_p) >= h;
                });
        pref[i] = sum.query(pos);
        st.add(a[i].i, 1);
        sum.add(a[i].i, a[i].c-a[i].x);
    }
    fill(sum.v.begin(), sum.v.end(), 0);
    fill(st.v.begin(), st.v.end(), 0);
    vector<ll> suf(n, 1ll<<61);
    for (int i = n-1; i >= n-h; i--) {
        st.add(a[i].j, 1);
        sum.add(a[i].j, a[i].c+a[i].x);
    }
    for (int i = n-1-h; i >= 0; i--) {
        int pos = bs_first<int>(1, n+1, [&](int _p){
                return st.query(_p) >= h;
                });
        suf[i] = sum.query(pos);
        st.add(a[i].j, 1);
        sum.add(a[i].j, a[i].c+a[i].x);
    }
    ll res = 1ll<<62;
    if (K & 1) {
        for (int i = h; i < n-h; i++) {
            ll tmp = pref[i] + a[i].c + suf[i];
            res = min(res, tmp);
        }
    } else {
        for (int i = h; i <= n-h; i++) {
            ll tmp = pref[i] + suf[i-1];
            res = min(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
