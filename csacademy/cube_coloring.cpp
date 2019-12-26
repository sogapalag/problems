#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 1005;

long long bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]);
        }
    }
}

// problem ask no-edge-adj same color, so each color can use at most two, less cases.
void solve() {
    bino_table();
    int n; cin >> n;
    int one = 0, two = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x==1)one++;
        else two++;
    }
    ll res = bino[one+two][6]*30;
    if (one+two-1>=4) res += bino[two][1]*bino[one+two-1][4] * 3;
    if (one+two-2>=2) res += bino[two][2]*bino[one+two-2][2];
    res += bino[two][3];
    cout << res;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
