#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> p[6];
int col[6][6];
void solve() {
    int n, k;
    cin >> n >> k;
    // skip
    if (n > 5) {cout << -1; return;}
    vector<vector<int>> a(n);
    memset(col, 0, sizeof col);
    int sum = 0;
    function<bool(int)> dfs = [&](int i){
        if (i == n) {
            if (sum == k) {
                cout << "POSSIBLE\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        cout << a[i][j] << ' ';
                    }cout << '\n';
                }
            }
            return sum == k;
        }
        for (auto& q: p[n]) {
            bool fail = false;
            for (int j = 0; j < n; j++) {
                fail |= (++col[j][q[j]] > 1);
            }
            if (!fail) {
                a[i] = q;
                if (sum+a[i][i] > k) goto nxt;
                sum += a[i][i];
                if (dfs(i+1)) return true;
                sum -= a[i][i];
            }
            nxt:;
            for (int j = 0; j < n; j++) {
                --col[j][q[j]];
            }
        }
        return false;
    };
    if (!dfs(0)) {
        cout << "IMPOSSIBLE\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 1; i <= 5; i++) {
        vector<int> a(i);
        iota(a.begin(), a.end(), 1);
        do {
            p[i].push_back(a);
        } while (next_permutation(a.begin(), a.end()));
    }
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
