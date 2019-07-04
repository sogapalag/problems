#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    int E = p[n];
    vector<bool> can_forward(n+1, false);
    vector<set<int>> to_right(n+1);
    for (int _ = 0; _ < m; _++) {
        int x, y;
        cin >> x >> y;
        if (y == E) {
            can_forward[x] = true;
        } else {
            to_right[x].insert(y);
        }
    }
    int res = 0;
    vector<int> block;
    for (int i = n-1; i >= 1; i--) {
        if (can_forward[p[i]]) {
            if (to_right[p[i]].size() < block.size()) {
                block.emplace_back(p[i]);
                continue;
            }
            bool T = true;
            for (auto& x: block) {
                if (to_right[p[i]].find(x) == to_right[p[i]].end()) {
                    T = false; break;
                }
            }
            if (T) {
                res++;
            } else {
                block.emplace_back(p[i]);
            }
        } else {
            block.emplace_back(p[i]);
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
