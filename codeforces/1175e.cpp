#include <bits/stdc++.h>

using namespace std;


const int N = 5e5+10;
const int L = 19; 

int st[L][N+1];

// sparse table, store can use 2^j to expand.
// for those can 2^j reach, but could not expand any more, still set 0.
void solve() {
    memset(st, 0, sizeof st);
    int n, m;
    cin >> n >> m;
    vector<int> a(N+1, 0);
    for (int _ = 1; _ <= n; _++) {
        int x, y;
        cin >> x >> y;
        x++; y++; // input could be 0.....
        a[x] = max(a[x], y);
    }
    vector<int> b(a);
    int mx = 0;
    for (int i = 1; i <= N; i++) {
        mx = max(mx, a[i]);
        b[i] = mx;
        a[i] = mx<=i ? 0 : mx;
    }

    for (int i = 1; i <= N; i++) {
        st[0][i] = a[i];
    }
    for (int j = 1; j < L; j++) {
        for (int i = 1; i <= N; i++) {
            st[j][i] = st[j-1][st[j-1][i]];
        }
    }
    
    while (m--) {
        int x, y;
        cin >> x >> y;
        x++; y++;
        int res = 0;
        for (int j = L-1; j >= 0; j--) {
            if (!st[j][x]) continue;
            if (st[j][x] < y) {
                res += 1 << j;
                x = st[j][x];
            }
        }
        res = b[x]>=y ? res+1 : -1;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
