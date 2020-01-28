#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 12; 
int a[N][N];
int c[N][N];

const int MOD = 1e9+7; 

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    if (n+m-1 > k) {
        cout << 0; return;
    }
    vector<int> cnt(k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j]; --a[i][j];
            if (a[i][j] != -1) cnt[a[i][j]]++;
        }
    }

    function<ll(int,int)> explore = [&](int x, int y){
        if (y > m) x++,y=1;
        if (x == n+1) {
            return 1ll;
        }
        int msk = c[x-1][y]|c[x][y-1];
        c[x][y] = msk;
        int co = a[x][y];
        // early leaving
        if (n+m - x-y > k - __builtin_popcount(msk)) return 0ll;

        ll res = 0;
        if (co != -1) {
            if (msk>>co&1) return 0ll;
            c[x][y] |= 1<<co;
            res += explore(x,y+1);
            c[x][y] ^= 1<<co;
        } else {
            int buff = -1; // avoid dup.
            for (int co = 0; co < k; co++) {
                if (msk>>co&1) continue;
                c[x][y] |= 1<<co;
                cnt[co]++;
                if (cnt[co] == 1) { // new
                    res += buff != -1 ? buff : buff=explore(x, y+1);
                } else res += explore(x, y+1);
                cnt[co]--;
                c[x][y] ^= 1<<co;
                res %= MOD;
            }
        }
        return res%MOD;
    };

    cout << explore(1,1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
