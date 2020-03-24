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
// by consider mid AA|BB, we can have L*R contribution.
// by fix len=k, consider AA. canonical form contain points i,j
//    thus by i,j left/right expand, note i,j contribute to L,R continuous range.(thus prefix-delta)
//          i
//   [<-l-> | <-r-> ]
//                   j=i+k
//            [<-l-> | <-r-> ]
//  R[...]              L[...]
void solve() {
    string s; cin >> s;
    int n = s.size();
    SuffixArray a(s);
    reverse(s.begin(), s.end());
    SuffixArray b(s);
    vector<int> L(n + 1), R(n + 1);
    for (int k = 1; k*2 <= n; k++) {
        for (int i = 0, j = i+k; j < n; i = j, j += k) {
            int r = min(k, a.get_lcp(i, j));
            int l = min(k, b.get_lcp(n-i-1, n-j-1));
            int extra = r+l-1 - k;
            if (extra >= 0) {
                R[i-l+1]++; R[i-l+extra+2]--;
                L[j+r-extra-1]++; L[j+r]--;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        L[i+1] += L[i];
        R[i+1] += R[i];
    }
    ll res = 0;
    for (int i = 1; i < n; i++) {
        res += L[i-1] *1ll* R[i];
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
