#include <bits/stdc++.h>

using namespace std;

const int N = 1024; 
char ts[N][N];

// ++++++ pattern
// another much easy pattern
// ..
// ...
//  ...
//   ..
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a;
    for (int i = 1; i <= n; i++) {
        a.emplace_back(2*i, 1);
        a.emplace_back(2*i, -1);
        a.emplace_back(2*i, 2);
        a.emplace_back(2*i, -2);
    }
    for (int i = 0; i <= 2*n+2; i++) {
        a.emplace_back(i, 0);
    }
    for (int i = 1; i <= n/2; i++) {
        a.emplace_back(4*i-1, 2);
        a.emplace_back(4*i-1, -2);
    }
    if (n&1) {
        for (int y = 1; y <= 4; y++) {
            a.emplace_back(0, y);
        }
        for (int x = 1; x <= 2*n; x++) {
            a.emplace_back(x, 4);
        }
        a.emplace_back(2*n, 3);
        a.emplace_back(2*n+1, -2);
        a.emplace_back(2*n+2, -2);
        a.emplace_back(2*n+2, -1);
    } else {
        for (int y = 1; y <= 4; y++) {
            a.emplace_back(0, y);
        }
        for (int x = 1; x <= 2*n+2; x++) {
            a.emplace_back(x, 4);
        }
        for (int y = 1; y <= 3; y++) {
            a.emplace_back(2*n+2, y);
        }
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    if (0) {
        memset(ts, '#', sizeof ts);
        const int Z = 6;
        for (auto& _: a) {
            int x,y;
            tie(x,y) = _;
            ts[x][y+Z] = '.';
        }
        for (int i = 0; i <= 200; i++) {
            for (int j = 0; j <= 15; j++) {
                cout << ts[i][j];
            }cout << '\n';
        }
    }
    cout << a.size() << "\n";
    for (auto& _: a) {
        int x,y;
        tie(x,y) = _;
        cout << x << ' ' << y << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
