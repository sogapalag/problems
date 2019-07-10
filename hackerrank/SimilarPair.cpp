#include <bits/stdc++.h>

using namespace std;

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

// BIT as set, count # in range
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n+1, 0);
    vector<vector<int>> g(n+1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[y] = x;
        g[x].emplace_back(y);
    }
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (!p[i]) root = i;
    }
    assert(root > 0);
    Fenwick<int> st(n);
    long long res = 0;
    function<void(int)> dfs = [&](int u){
        int l = max(0, u-k);
        int r = min(n, u+k);
        res += st.query(l, r);
        st.add(u, 1);
        for (int v: g[u]) {
            dfs(v);
        }
        st.add(u, -1);
    };
    dfs(root);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
