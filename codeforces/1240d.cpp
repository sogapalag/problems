#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> R(n,-1); // first matched ]
    vector<map<int,int>> nxt(n+1); //     x [i,..] x  i.e. before a_i is x, get matched x' idx
    nxt[n-1][a[n-1]] = n-1;
    for (int i = n-2; i >= 0; i--) {
        int x = a[i];
        if (nxt[i+1].find(x) != nxt[i+1].end()) {
            R[i] = nxt[i+1][x];
            swap(nxt[i], nxt[R[i]+1]);
            // swap, prevent slow, since the block is elimated,
            // find x from i, just like from R[i]+1
        }
        nxt[i][x] = i; // except a[i]
    }
    
    ll res = 0;
    vector<ll> dp(n+1, 0); // valid cnt as i as start
    for (int i = n-2; i >= 0; i--) {
        if (R[i] == -1) continue;
        dp[i] = dp[R[i]+1] + 1;
        res += dp[i];
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
