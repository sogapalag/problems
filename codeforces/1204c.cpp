#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 111; 

int d[N][N];

void solve() {
    int n; cin >> n;
    memset(d, INF, sizeof d);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1')
                d[i][j] = 1;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {// for negative
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    int m; cin >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    vector<int> res;
    res.emplace_back(0);
    int i = 1;
    while (i < m) {
        int c = res.back();
        assert(i == c+1);
        while (i+1<m && a[i+1] != a[c] && d[a[c]][a[i+1]] == i+1-c) {
            i++;
        }
        res.emplace_back(i);
        i++;
    }
    int k = res.size();
    cout << k << "\n";
    for (auto& x: res) {
        cout << a[x]+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
