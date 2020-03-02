#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 100005; 
int dp[62][N]; // 0..i) bits has j carried, min-cost

// first transform a, problem is ask add some t>=0 to all a, s.t. sum popcount(t+x) is minimal.
// for i bit, t set 0/1, x 0/1, x's prev carry 0/1 => cost , carry
// the key is note, suppose #prev carry = j, then they must be suffix under sort by (x&MSK).
//   since (t+x) wanna >= 1<<i. we don't need to know what exactly t or x. But we can ensure they must be suffix 
// then dp relation can separate carry or not before, how many 0/1 in each, t 0/1, to decide next state.
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    {
        ll mx = 0;
        for (auto& x: a) {
            cin >> x;
            mx = max(mx, x);
        }
        for (auto& x: a) {
            x = mx - x;
        }
    }

    auto sort_by = [&](int i){
        const ll MSK = (1ll<<i)-1; 
        sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return (u&MSK) < (v&MSK);
        });
    };
    vector<int> pref(n + 1);
    auto prep = [&](int k){
        for (int i = 0; i < n; i++) {
            pref[i+1] = pref[i] + (a[i]>>k&1);
        }
    };
    auto cnt1 = [&](int l, int r){
        return pref[r] - pref[l];
    };
    auto cnt0 = [&](int l, int r){
        return r-l - cnt1(l,r);
    };
    auto mini = [](int& x, int y){
        if (x > y) x = y;
    };
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    //    t{0/1} | (prev carried)
    //       0   | 0<-
    //       1   | 0
    //       1   | 0
    //       .   | .
    //       0   | 1    ^   
    //       .   | .    j
    //       1   | 1    . 
    for (int i = 0; i < 61; i++) {
        if (i) sort_by(i);
        prep(i);
        for (int j = 0; j <= n; j++) {
            // t=0
            {
                int carry = cnt1(n-j, n);
                int cost = cnt1(0, n-j) + cnt0(n-j, n);
                mini(dp[i+1][carry], dp[i][j] + cost); 
            }
            // t=1
            {
                int carry = cnt1(0, n-j) + j;
                int cost = cnt0(0, n-j) + cnt1(n-j, n);
                mini(dp[i+1][carry], dp[i][j] + cost); 
            }
        }
    }
    cout << dp[61][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
