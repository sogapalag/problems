#include <bits/stdc++.h>

using namespace std;

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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n+1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        g[x].emplace_back(i);
    }
    vector<int> arm(n+1);
    function<void(int)> dfs = [&](int u){
        int mx = 0;
        for (int v: g[u]) {
            dfs(v);
            mx = max(mx, arm[v]);
        }
        arm[u] = 1 + mx;
    };
    dfs(0);
    int m = arm[0];
    vector<int> cnt(m);
    for (int i = 1; i <= n; i++) {
        cnt[arm[i]]++;
    }
    vector<int> b(m+1);
    b[1] = n;
    for (int i = 2; i <= m; i++) {
        b[i] = b[i-1] - cnt[i-1];
    }
    assert(b[m]==0);

    while (q--) {
        int x; cin >> x;
        int i = bs_first<int>(1, m+1, [&](int i){
                return b[i] <= x;
                });
        if (i>1 && b[i-1]-x <= x - b[i]) i = i-1;
        cout << i << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
