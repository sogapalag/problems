#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> p(m);
        for (int j = 0; j < m; j++) {
            cin >> p[j];
        }
        sort(p.begin(), p.end());
        for (int j = 0; j < m; j++) {
            p[j] += 2 * j + 1;
        }
        for (int x: p) {
            pq.emplace(x);
        }
        for (int k = 1; k <= a[i]; k++) {
            res += pq.top();
            pq.pop();
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
