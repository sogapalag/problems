#include <bits/stdc++.h>

using namespace std;

const int MSK = 1<<20; 
int dp[1<<20];// max_sub:msk len(sub)

void solve() {
    string s; cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        int msk = 0;
        for (int j = 0; j < 20; j++) {
            if (i+j >= n) break;
            int x = 1 << (s[i+j] - 'a');
            if (msk & x) break;
            msk |= x;
            dp[msk] = j+1;
        }
    }

    // 2^20 ~ 3^20, exact?
    //int res = 0;
    //for (int i = (1<<20)-1; i > 0; i--) {
    //    if (!dp[i]) continue;
    //    res = max(res, __builtin_popcount(i));
    //    int msk = ~i;
    //    int x = 1 << (32-__builtin_clz(i));
    //    msk &= x-1;
    //    for (int sub = msk; sub > 0; (sub-=1)&=msk) {
    //        if (!dp[sub]) continue;
    //        res = max(res, __builtin_popcount(i^sub));
    //    }
    //}
    //cout << res;
    
    for (int msk = 1; msk < MSK; msk++) {
        for (int j = 0; j < 20; j++) {
            if (msk & (1<<j)) continue;
            dp[msk^(1<<j)] = max(dp[msk^(1<<j)], dp[msk]);
        }
    }
    int res = 0;
    for (int msk = 0; msk < MSK; msk++) {
        int rev = (MSK-1) ^ msk;
        res = max(res, dp[msk]+dp[rev]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
