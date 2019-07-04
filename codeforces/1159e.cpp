#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<vector<int>> g(n+2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1)
            a[i] = i+1;
        g[a[i]].emplace_back(i);
    }
    vector<int> p(n+2, 0);
    int cnt = n+1;
    function<void(int)> dfs = [&](int u){
        p[u] = cnt--;
        for (int v: g[u]) {
            if (!p[v]) {
                dfs(v);
            }
        }
    };
    dfs(n+1);
    vector<int> b(n+1);
    vector<int> stk; stk.reserve(n);
    for (int i = 1; i <= n+1; i++) {
        if (!p[i]) {
            cout << -1 << "\n";
            return;
        }
        while (!stk.empty() && p[i] > p[stk.back()]) {
            b[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            cout << -1 << "\n";
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << p[i] << ' ';
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
