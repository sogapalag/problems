#include <bits/stdc++.h>

using namespace std;


// x,y independent
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> X(m+1), Y(m+1);
    int xnt = 0, ynt = 0;
    for (int _ = 0; _ < n; _++) {
        int x, y;
        cin >> x >> y;
        string s; cin >> s;
        char c = s[0];
        if (c == 'W' || c == 'E') {
            if (c == 'W') {
                xnt++;
                X[x]--;
            } else {
                X[x+1]++;
            }
        } else {
            if (c == 'S') {
                ynt++;
                Y[y]--;
            } else {
                Y[y+1]++;
            }
        }
    }
    X[0] = xnt, Y[0] = ynt;
    int mx = X[0], x = 0;
    int my = Y[0], y = 0;
    for (int i = 1; i <= m; i++) {
        X[i] += X[i-1];
        Y[i] += Y[i-1];
        if (X[i] > mx) {
            mx = X[i]; x = i;
        }
        if (Y[i] > my) {
            my = Y[i]; y = i;
        }
    }
    cout << x << ' ' << y << '\n';
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
