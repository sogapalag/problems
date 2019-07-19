#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 13; // 20;
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
using ll=long long ;
void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int g, x, y, z;
    cin >> g >> x >> y >> z;
    vector<int> row(m);
    vector<vector<int>> col(m-b+1, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            row[j] = g;
            g = ((ll)g*x+y) % z;
        }
        Rmq<> rmq(row);
        for (int j = 0; j < m-b+1; j++) {
            col[j][i] = rmq.query(j, j+b);
        }
    }
    ll res = 0;
    for (auto& c: col) {
        Rmq<> rmq(c);
        for (int i = 0; i+a <= n; i++) {
            res += rmq.query(i, i+a);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
