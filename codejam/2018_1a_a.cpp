#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,h,v;
    cin >> n >> m >> h >> v;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tot += s[i][j] == '@';
        }
    }
    if (tot == 0) {
        cout << "POSSIBLE\n"; return;
    }
    if (tot % ((h+1)*(v+1)) != 0) {
        cout << "IMPOSSIBLE\n"; return;
    }
    // if exist. then a,b as cut must be a solution
    vector<int> a;
    for (int i = 0, avg = tot/(h+1), sum = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += s[i][j] == '@';
        }
        //if (sum%avg==0) a.push_back(i+1);
        if (sum == avg*((int)a.size()+1)) a.push_back(i+1);
    }
    if ((int)a.size() != h+1) {
        cout << "IMPOSSIBLE\n"; return;
    }
    vector<int> b;
    for (int j = 0, avg = tot/(v+1), sum = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            sum += s[i][j] == '@';
        }
        //if (sum%avg==0) b.push_back(j+1);
        if (sum == avg*((int)b.size()+1)) b.push_back(j+1);
    }
    if ((int)b.size() != v+1) {
        cout << "IMPOSSIBLE\n"; return;
    }
    int block = tot / (h+1)/(v+1);
    for (int _i = 0; _i < (int)a.size(); _i++) {
        for (int _j = 0; _j < (int)b.size(); _j++) {
            int x = _i?a[_i-1]:0;
            int y = _j?b[_j-1]:0;
            int u = a[_i];
            int v = b[_j];
            int sum = 0;
            for (int i = x; i < u; i++) {
                for (int j = y; j < v; j++) {
                    sum += s[i][j] == '@';
                }
            }
            if (sum != block) {
                cout << "IMPOSSIBLE\n"; return;
            }
        }
    }
    cout << "POSSIBLE\n";
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
