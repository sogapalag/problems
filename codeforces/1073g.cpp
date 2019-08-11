#include <bits/stdc++.h>

using namespace std;

#define LOCAL
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
        for (int i = 0; i < n; i++) {
            lcp[i] = lcp[i+1];
        }
        lcp[n] = 0;
        r.init(lcp);
    }
    int get_lcp_by_rank(int a, int b) {
        if (a == b) return sa.size()-1 - sa[a];
        if (a > b) swap(a, b);
        return r.query(a, b);
    }
    int get_lcp(int u, int v) {
        if (u == v) return sa.size()-1 - u;
        return get_lcp_by_rank(rk[u], rk[v]);
    }
};

using ll=long long;


void solve() {
    int _, q;
    cin >> _ >> q;
    string s; cin >> s;
    SuffixArray SA(s);
 
    // note a is sorted by rank, thus  lcp(i,k) = min_{i<j<=k} lcp(j-1,j) for new k, i.e. decreasing
    // so use stack or map, maintain [..k] lcp_len/cnt
    auto sum_lcp = [&](vector<int>& a)->ll {
        int n = a.size();
        ll res = 0;
        vector<pair<int, int>> stk; stk.reserve(n);
        ll sum = 0; // potential sum of lcp[.., k]
        for (int i = 0; i < n; i++) {
            int lcp = i==0? 0 : SA.get_lcp_by_rank(a[i-1], a[i]);
            int cnt = 1;
            while (!stk.empty() && lcp <= stk.back().first) {
                int len, c;
                tie(len, c) = stk.back();
                sum -= (ll) c * (len - lcp);
                cnt += c;
                stk.pop_back();
            }

            stk.emplace_back(lcp, cnt);
            sum += lcp;
            res += sum;
        }
        return res;
    };

    while (q--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++) {
            cin >> a[i]; a[i] = SA.rk[--a[i]];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i]; b[i] = SA.rk[--b[i]];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ll res = sum_lcp(a) + sum_lcp(b);
        vector<int> v(n+m);
        merge(a.begin(), a.end(), b.begin(), b.end(), v.begin());
        res = sum_lcp(v) - res;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
