#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
const int L = 20; 
const int MSK = 1<<L; 
ll d[L][L];
ll ss[L][MSK];
ll dp[MSK];

void sub_sum(int i){
    vector<ll> pos(L, 0); // [j..0] : + - - - - 
    ll sum = 0;
    for (int j = 0; j < L; j++) {
        pos[j] = d[i][j] - sum;
        sum += d[i][j];
    }
    sum = 0;
    // since ...1000 by ...0111 add +---
    for (int msk = 1; msk < MSK; msk++) {
        sum += pos[__builtin_ctz(msk)];
        ss[i][msk] = sum;
    }
}

// pre_calc subset sum, Down O(20), about 5x fast
void solve() {
    int n; cin >> n;
    vector<int> cnt(L, 0);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x; x--;
        for (int i = 0; i < L; i++) {
            d[x][i] += cnt[i];
        }
        cnt[x]++;
    }
    for (int i = 0; i < L; i++) {
        d[i][i] = 0;
        sub_sum(i);
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int msk = 1; msk < MSK; msk++) {
        //for (int i = 0; i < L; i++) {
        //    if (msk & (1<<i)) {
        //        dp[msk] = min(dp[msk], dp[msk^(1<<i)] + ss[i][msk]);
        //    }
        //}
        for (int p = msk; p > 0; p -= p&(-p)) { // not sigificantly fast
            int i = __builtin_ctz(p);
            dp[msk] = min(dp[msk], dp[msk^(1<<i)] + ss[i][msk]);
        }
    }
    cout << dp[MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
