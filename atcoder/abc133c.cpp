#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n = 2019;
    int x, y;
    cin >> x >> y;
    if (y-x >= n-1){
        cout << 0; return;
    }
    int res = 2018;
    for (int i = x; i <= y; i++) {
        for (int j = i+1; j <= y; j++) {
            int u = i%n, v = j%n;
            int tmp = u*v % n;
            res = min(res, tmp);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
