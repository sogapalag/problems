#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 20;
    int k;
    int n;
    vector<int> st[LOG];
    void init(vector<T> _v) { // pass in vec[0, n)
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

struct SuffixArray {
    vector<int> sa, rk, lcp;
    Rmq<int> r;

    SuffixArray(const string& s) {
        int n = s.size();
        sa.resize(n+1); rk.resize(n+1); lcp.resize(n+1);
        for (int i = 0; i < n; i++) {
            rk[i] = (int)s[i]+1;
        }
        rk[n] = 0;
        auto S = rk;

        int N = sa.size(), m = 260;
        auto& x = rk;
        auto& y = lcp;
        auto _sort = [&](){
            vector<int> cnt(m,0);
            for (int i = 0; i < N; i++) cnt[x[y[i]]]++;
            for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];
            for (int i = N-1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        };
        iota(y.begin(), y.end(), 0); _sort();
        for (int k = 1, p = 0; k <= N; k <<= 1, p = 0) {
            for (int i = N-k; i < N; i++) y[p++] = i;
            for (int i = 0; i < N; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
            _sort();
            swap(x, y);
            x[sa[0]] = 0;
            p = 1;
            for (int i = 1; i < N; i++) {
                p += y[sa[i]] != y[sa[i-1]] || y[sa[i]+k] != y[sa[i-1]+k];
                x[sa[i]] = p-1;
            }
            if ((m=p) >= N) break;
        }

        // rk*sa = I
        for (int i = 0; i < N; i++) {
            rk[sa[i]] = i;
        }
        lcp[0] = 0;
        for (int i = 0, h = 0; i < N; i++) {
            if (!rk[i]) continue;
            if (h) h--;
            while (S[i+h] == S[sa[rk[i]-1] + h]) {
                h++;
            }
            lcp[rk[i]] = h;
        }
        // to 0-based, lcp[i] = lcp(rk=i, rk=i+1)
        {
            for (int i = 0; i < n; i++) {
                lcp[i] = lcp[i+1];
            }
            lcp[n] = 0;
        }
        r.init(lcp);
    }
    int get_lcp_by_rank(int a, int b) {
        if (a == b) return sa.size()-1 - sa[a];
        if (a > b) swap(a, b);
        return r.query(a, b);
    }
    // s[u..], s[v..]
    int get_lcp(int u, int v) {
        if (u == v) return sa.size()-1 - u;
        return get_lcp_by_rank(rk[u], rk[v]);
    }
};

using ll=long long;
struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    vector<int> mx, mi;
    ll sum = 0;
    ll prod = -1e18;
    
    Dsu(int _n) : n(_n)
        , p(n)
        , r(n)
        , mx(n)
        , mi(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        sum += r[x] * 1ll * r[y];
        prod = max({prod, mx[x]*1ll*mx[y], mi[x]*1ll*mi[y]});
        mx[x] = max(mx[x], mx[y]);
        mi[x] = min(mi[x], mi[y]);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
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

// prep a by rank.
// key: dsu. thus by lcp dec order, #exactly lcp=new_val := sz[u]*sz[v]
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    SuffixArray sa(s);
dbg(sa.rk);
dbg(sa.sa);
dbg(sa.lcp);
    vector<vector<int>> ess(n);
    for (int i = 0; i < n-1; i++) {
        // lcp[1..n) repre. relation of original string
        ess[sa.lcp[i+1]].push_back(i);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[sa.rk[i] - 1] = x;
    }
    Dsu d(n);
    d.mx = d.mi = a;
    vector<ll> res(n), ans(n);
    for (int lcp = n-1; lcp >= 0; lcp--) {
        for (int i: ess[lcp]) {
            d.join(i, i+1);
        }
        res[lcp] = d.sum;
        ans[lcp] = d.sum > 0 ? d.prod : 0;
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << ' ' << ans[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
