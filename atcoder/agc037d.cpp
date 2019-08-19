#include <bits/stdc++.h>

using namespace std;


// Hall's matching. poker match
void solve() {
    int n, m;
    cin >> n >> m;
    auto club = [&](int x){
        return x/m;
    };
    vector<int> a[101][101];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; x--;
            a[i][club(x)].emplace_back(x);
        }
    }
    int b[101][101];
    // for each col, find match
    for (int j = 0; j < m; j++) {
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < n; c++) {
                if (!a[i][c].empty())
                    g[i].emplace_back(c);
            }
        }
        vector<bool> trk(n, false);
        vector<int> left(n, -1);
        function<bool(int)> dfs = [&](int l){
            if (trk[l]) return false;
            trk[l] = true;
            for (int r: g[l]) {
                if (left[r] == -1 || dfs(left[r])) {
                    left[r] = l;
                    return true;
                }
            }
            return false;
        };
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        assert(cnt == n); // Hall's
        for (int c = 0; c < n; c++) {
            int i = left[c];
            b[i][j] = a[i][c].back(); a[i][c].pop_back();
        }
    }
    int c[101][101];
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            c[j][i] = b[i][j];
        }
        sort(c[j], c[j]+n, [&](int x, int y){return club(x) < club(y);});
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << b[i][j]+1 << ' ';
        }cout << "\n";
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << c[j][i]+1 << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
