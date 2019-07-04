#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> a(n+m);
    vector<vector<int>> b(n+m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i+j].emplace_back(x);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            b[i+j].emplace_back(x);
        }
    }
    for (int d = 0; d < n+m; d++) {
        sort(a[d].begin(), a[d].end());
        sort(b[d].begin(), b[d].end());
        bool T = true;
        for (int i = 0; i < (int)a[d].size(); i++) {
            T &= a[d][i] == b[d][i];
        }
        if (!T) {
            cout << "NO"; return;
        }
    }
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
