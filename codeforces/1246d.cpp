#include <bits/stdc++.h>

using namespace std;


// from longest path, bottom to up,
// v, if its'pa u's has another w, v move to w's. thus depth +1 for sure
void solve() {
    int n; cin >> n;
    vector<int> pa(n);
    vector<int> d(n);
    vector<set<int>> g(n);
    for (int i = 1; i < n; i++) {
        cin >> pa[i];
        d[i] = d[pa[i]] + 1;
        g[pa[i]].insert(i);
    }
    vector<int> res;
    int v = max_element(d.begin(), d.end()) - d.begin();
    int x = v;
    while (v) {
        int u = pa[v];
        if (g[u].size() == 1) {
            v = u;
        } else {
            res.emplace_back(v);
            g[u].erase(v);
            int w = *g[u].begin();
            pa[v] = w;
            g[w].insert(v);
        }
    }
    vector<int> line(n);
    for (int i = n-1; i >= 0; i--) {
        line[i] = x;
        x = pa[x];
    }
    reverse(res.begin(), res.end());
    for (auto& x: line) {
        cout << x << ' ';
    }cout << "\n";
    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
