#include <bits/stdc++.h>

using namespace std;


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

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] < raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return raw[query_id(l, r)];
    }
};

// sparse table, track the link -> -> ->..
// then for each l, get the minimum r to satisfy.
// then each query, RMQ <= r
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> p(n+1);
    vector<int> nex(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        nex[p[i-1]] = p[i];
    }
    p[0] = p[n];
    nex[p[0]] = p[1];
    dbg(nex);
    vector<int> a(m+1);
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    vector<int> las(n+1, m+1);
    vector<vector<int>> to(19, vector<int>(m+2, m+1));
    for (int i = m; i >= 1; i--) {
        int nx = nex[a[i]];
        to[0][i] = las[nx];
        las[a[i]] = i;
    }
    dbg(las);
    for (int j = 1; j < 19; j++) {
        for (int i = 1; i <= m; i++) {
            to[j][i] = to[j-1][to[j-1][i]];
        }
    }
    vector<int> nd(m);
    for (int i = 0; i < m; i++) {
        int k = i+1;
        int x = n-1;
        while (x) {
            int j = 31 - __builtin_clz(x);
            k = to[j][k];
            x -= 1 << j;
        }
        nd[i] = k;
    }
    dbg(nd, to);

    Rmq<> rmq(nd);
    while (q--) {
        int l, r;
        cin >> l >> r;
        int res = rmq.query(l-1, r) <= r ? 1 : 0;
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
