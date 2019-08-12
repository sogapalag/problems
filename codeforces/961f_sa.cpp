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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    SuffixArray SA(s);
    int m = n/2;
    vector<int> len(m);// len[i]: i as center, max valid half-length. single=1
    for (int i = 0; i < m; i++) {
        int j = n-i-1;
        if (s[i] != s[j]) {
            len[i] = 0; continue;
        }
        int lim = i+2;
        len[i] = bs_last<int>(1, lim, [&](int x){
                // valid
                return SA.get_lcp(i-x+1, j-x+1) >= 2*x-1;
                });
    }
    vector<int> mx(m, -1);
    for (int i = 0; i < m; i++) {
        if (len[i] > 0) {
            int l = i-len[i]+1;
            mx[l] = max(mx[l], 2*len[i]-1);// when l, max valid length
        }
    }
    // res[i]: variant-prefix max, since valid iff the valid box[l,r] that l<=i
    for (int i = 1; i < m; i++) {
        mx[i] = max(mx[i], mx[i-1]-2); // whenever move right 1 step, before valid length -2
    }
    for (int i = 0; i < m; i++) {
        if (mx[i] <= 0) mx[i] = -1;
        cout << mx[i] << ' ';
    }
    if (n&1) cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
