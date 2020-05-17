#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    vector<vector<pair<int,int>>> g(26);
    vector<int> a(26);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[s[i][j]-'A'].emplace_back(i, j);
            ++a[s[i][j]-'A'];
        }
    }
    vector<bool> trk(26);
    int cnt = 0;
    string res;
    while (cnt < n*m) {
        for (int c = 0; c < 26; c++) if(!g[c].empty() && !trk[c]){
            for (auto& p: g[c]) {
                int i,j;
                tie(i,j) = p;
                // unstable?
                if (i+1<n && s[i+1][j]!=s[i][j] && !trk[s[i+1][j]-'A']) {
                    goto nxt;
                }
            }
            res.push_back(char('A'+c));
            trk[c] = true;
            cnt += a[c];
            goto suc;
            nxt:;
        }
        cout << "-1\n"; return;
suc:;
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
