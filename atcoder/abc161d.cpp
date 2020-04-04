#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

int dp[64][11][2];
using ll=long long;
void solve() {
    int K; cin >> K;
    auto ck = [&](ll x){
        vector<int> d;
        while (x > 0) {
            d.push_back(x%10);
            x/=10;
        }
        memset(dp, 0, sizeof dp);
        d.push_back(0);
        reverse(d.begin(), d.end());
        int n = d.size();
        dp[0][10][0] = 1; // 10=prefix 0
        for (int i = 0; i < n; i++) {
            int z = d[i];
            for (int j = 0; j <= 10; j++) {
                for (int k:{0,1}) {
                    if (j == 10) {
                        for (int jj = 1; jj < 10; jj++) if(k || jj<=z){
                            dp[i+1][jj][k||jj<z] += dp[i][j][k];
                        }
                        dp[i+1][10][k||0<z] += dp[i][j][k];
                    } else {
                        for (int jj:{j-1,j,j+1})if(0<=jj && jj<10){
                            if (k || jj <= z) {
                                dp[i+1][jj][k||jj<z] += dp[i][j][k];
                            }
                        }
                    }
                }
            }
        }
        int res = 0;
        for (int j = 0; j < 10; j++) {
            res += dp[n][j][0] + dp[n][j][1];
        }
        return res >= K;
    };
    ll res = bs_first<ll>(1, 1e15, ck);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
