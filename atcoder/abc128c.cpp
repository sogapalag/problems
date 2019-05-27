#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> k(m);
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        for (int j = 0; j < x; j++) {
            int y; cin >> y;
            k[i].emplace_back(y-1);
        }
    }
    vector<int> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }
    int res = 0;
    for (int i = 0; i < (1<<n); i++) {
        bool flag = true;
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            for (int x: k[j]) {
                if (i & (1<<x)) cnt++;
            }
            if (cnt%2 != p[j]) {
                flag = false;
                break;
            }
        }
        if (flag) res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
