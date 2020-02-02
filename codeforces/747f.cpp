#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int H = 16; 
int cnt[H];
ll fac[H];
void prep() {
    fac[0] = 1;
    for (int i = 1; i < H; i++) {
        fac[i] = fac[i-1] * i;
    }
}
ll dp[H];
// multinorm
ll calc(int n) {
    memset(dp, 0, sizeof dp);
    dp[0] = fac[n];
    for (int i = 0; i < H; i++) {
        int x = cnt[i];
        for (int j = n; j >= 0; j--) {
            for (int k = 1; k <= x && j+k <= n; k++) {
                dp[j+k] += dp[j]/fac[k];
            }
        }
    }
    return dp[n];
}

void solve() {
    prep();
    ll k; int t;
    cin >> k >> t;
    k--;
    fill(cnt, cnt+H, t);
    // first non-zero, find length
    int n = 0, d = -1;
    cnt[1]--;
    for (; ;n++) {
        ll x = calc(n);
        if (15 * x > k) {
            d = k/x + 1;
            k -= (d-1)*x;
            break;
        }
        k -= 15 * x;
    }
    cnt[1]++;

    auto f = [](int d){
        if (d < 10) return char('0'+d);
        else return char('a'+d-10);
    };
    assert(n < 9 && d != -1);

    cout << f(d); cnt[d]--;
    // remain n pos
    while (n > 0) {
        n--;
        for (int i = 0; i < H; i++) {
            if (cnt[i] > 0) {
                cnt[i]--;
                ll x = calc(n);
                if (k < x) {
                    cout << f(i); break;
                }
                k -= x;
                cnt[i]++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
