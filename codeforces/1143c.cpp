#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> ch(n+1);
    vector<int> C(n+1);
    for (int i = 1; i <= n; i++) {
        int p, c;
        cin >> p >> c;
        C[i] = c;
        if (p != -1) {
            ch[p].emplace_back(i);
        } else C[i] = 0;
    }

    vector<int> res; res.reserve(n);
    for (int i = 1; i <= n; i++) {
        if (C[i]) {
            bool t = true;
            for (auto& k: ch[i]) {
                if (!C[k]) {
                    t = false; break;
                }
            }
            if (t) res.emplace_back(i);
        }
    }
    if (res.empty()) {
        cout << -1; return;
    }
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
