#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,_m,k;
    cin >> n >> _m >> k;
    const int MSK = 1<<k; 
    vector<pair<int, int>> a(n);
    vector<int> Xs;
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        x--;
        a[i] = {x,y};
        Xs.push_back(x);
        Xs.push_back(y);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    int m = Xs.size();
    vector<vector<int>> add(m), del(m);
    for (int i = 0; i < n; i++) {
        int x,y;
        tie(x,y) = a[i];
        add[lower_bound(Xs.begin(), Xs.end(), x) - Xs.begin()].push_back(i);
        del[lower_bound(Xs.begin(), Xs.end(), y) - Xs.begin()].push_back(i);
    }

    vector<int> pos(n, -1);
    vector<int> R(k, -1);
    vector<int> dp(MSK, -1e8); // dp[msk], the msk still open(
    dp[0] = 0;
    // seg, could used seg-mask
    for (int _ = 0, seg = 0, lx = 0; _ < m; _++) {
        int x = Xs[_];
        // between
        for (int sub = seg; sub >= 0; (sub-=1)&=seg) {
            if (__builtin_popcount(sub)&1) {
                dp[sub] += x - lx;
            }
            if (sub == 0) break;
        }
        // del
        for (int i: del[_]) {
            i = pos[i];
            assert(0<=i && i<k);
            seg ^= 1<<i;
            for (int msk = 0; msk < MSK; msk++) {
                if (msk>>i&1) {
                    dp[msk^1<<i] = max(dp[msk^1<<i], dp[msk]);
                    dp[msk] = -1e8; // must closed.
                }
            }
            R[i] = -1;
        }
        // add
        for (int i: add[_]) {
            int j = 0;
            while (R[j] != -1) {
                j++;
            }
            R[j] = i; pos[i] = j;
            seg ^= 1<<j;
            for (int msk = MSK; msk >= 0; msk--) {
                if (msk>>j&1) {
                    // if open
                    dp[msk] = max(dp[msk], dp[msk^1<<j]);
                }
            }
        }
        lx = x;
    }
    cout << *max_element(dp.begin(), dp.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
