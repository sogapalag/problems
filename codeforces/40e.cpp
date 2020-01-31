#include <bits/stdc++.h>

using namespace std;

// k<max, implies one row reserve, to be decided by all other rows. then check each row free-dim
void solve() {
    int n,m;
    cin >> n >> m;
    if ((n^m)&1) {
        cout << 0; return;
    }
    bool traned = false;
    if (n < m) swap(n,m), traned = true;

    vector<int> cnt(n), sum(n);
    int k; cin >> k;
    for (int _ = 0; _ < k; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        if(traned) swap(x,y);
        x--;y--;
        cnt[x]++;
        if (z==-1) sum[x]^=1;
    }

    int p; cin >> p;
    int fre = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i]==m && sum[i]!=1) {
            cout << 0; return;
        } else {
            fre += max(m-cnt[i]-1, 0);
        }
    }
    fre -= m-1; // reserved row

    long long res = 1;
    for (int _ = 0; _ < fre; _++) {
        (res *= 2) %= p;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
