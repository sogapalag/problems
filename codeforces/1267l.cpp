#include <bits/stdc++.h>

using namespace std;

const int N = 1024; 
char a[N][N];

// a
// b
// c e
// c f g
// c f h h i ..
// .
// .
// greedy fill prefix-same positions first.
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    string s; cin >> s;
    sort(s.begin(), s.end());
    int x = 0, l = 0, r = k;
    for (int j = 0; j < m; j++) {
        for (int i = l; i < r; i++) {
            a[i][j] = s[x++];
        }
        for (int i = r-1; i >= l; i--) {
            if (a[i][j] != a[r-1][j]) {
                l = i+1; break;
            }
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (!a[i][j]) {
                a[i][j] = s[x++];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
