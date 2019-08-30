#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+10; 
const int L = 20; 
int a[N][L];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        a[x][0]++;
    }
    int res = 1e8;
    for (int i = N-1; i >= 0; i--) {
        int cost = 0;
        int cnt = k;
        for (int j = 0; j < L; j++) {
            int t = min(a[i][j], cnt);
            cnt -= t;
            cost += t*j;
        }
        if (cnt == 0) res = min(res, cost);
        for (int j = 0; j < L-1; j++) {
            a[i>>1][j+1] += a[i][j];
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
