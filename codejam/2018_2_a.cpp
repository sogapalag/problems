#include <bits/stdc++.h>

using namespace std;

const int N = 111; 
char s[N][N];
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    if (!a[0] || !a.back()) {
        cout << "IMPOSSIBLE\n"; return;
    }
    memset(s, '.', sizeof s);
    vector<int> to(n);
    for (int i = 0, x = 0; i < n; i++) {
        while (a[i] > 0) {
            to[x++] = i;
            --a[i];
        }
    }
    int row = 1; // problem ask for min row
    for (int x = 0; x < n; x++) {
        int i = to[x];
        if (i==x)continue;
        row = max(row, abs(i-x) + 1);
        if (i < x) {
            for (int k = i+1; k <= x; k++) {
                s[0 + (x-k)][k] = '/';
            }
        } else {
            for (int k = x; k < i; k++) {
                s[0 + (k-x)][k] = '\\';
            }
        }
    }
    cout << row << '\n';
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < n; j++) {
            cout << s[i][j];
        }cout << '\n';
    }
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
