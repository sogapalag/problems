#include <bits/stdc++.h>

using namespace std;


// pick max/min to explore -1/+1
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> a(n);
    vector<bool> trk(n);
    priority_queue<pair<int,int>> pq;
    int k; cin >> k;
    for (int _ = 0; _ < k; _++) {
        int i, x;
        cin >> i >> x;
        i--;
        trk[i] = true;
        a[i] = x;
        pq.emplace(x, i);
    }
    while (!pq.empty()) {
        int x,i;
        tie(x,i) = pq.top(); pq.pop();
        for (int v: g[i]) {
            if (trk[v]) {
                if (abs(a[v]-x) != 1) {
                    cout << "No"; return;
                }
            } else {
                a[v] = x - 1;
                trk[v] = true;
                pq.emplace(a[v], v);
            }
        }
    }
    cout << "Yes\n";
    for (auto& x: a) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
