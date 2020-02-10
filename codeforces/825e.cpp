#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int>;

// WA assign 1..n, from indeg=0
// e.g.  4->1, 2->3,   a[2] = 1, but next step we should free 3, we should free 4 instead for to free 1 quick
void __solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> indeg(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        indeg[y]++;
        g[x].push_back(y);
    }
    priority_queue<pi, vector<pi>, greater<pi>> hp;
    for (int i = 0; i < n; i++) {
        hp.emplace(indeg[i], i);
    }
    vector<int> a(n, -1);
    int x = 0;
    while (!hp.empty()) {
        int d, u;
        tie(d, u) = hp.top(); hp.pop();
        if (a[u] != -1) continue;
        assert(d == 0);
        a[u] = x++;
        for (int v: g[u]) {
            hp.emplace(--indeg[v], v);
        }
    }
    for (auto& x: a) {
        cout << x+1 << ' ';
    }
}

// why other side work, seems dual. but note lexi is not dual(i.e. you cannot from right-comp)
// rigorous proof:
//   must a[v] = n.
//   suppose a[v] = x<n. then we shift a[..] = [x+1, n] -> [x,n-1], and let a[v]=n
//     one can see, shift, made each these pos smaller, 
//     although a[v]=n become larger, but note if a[v]=x, it implies some u<v, a[u]=n
//       i.e. when comp lexi, u<v comp-earlier a[u]=n -> n-1, 
//     lexi can become even smaller. by contradiction. QED
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> outdeg(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        outdeg[x]++;
        g[y].push_back(x);
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (outdeg[i] == 0) pq.push(i);
    }
    vector<int> a(n);
    for (int i = n; i >= 1; i--) {
        int v = pq.top(); pq.pop();
        a[v] = i;
        for (int u: g[v]) {
            --outdeg[u];
            if (outdeg[u] == 0) pq.push(u);
        }
    }
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
