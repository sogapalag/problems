#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int T = 256; 

void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<ll> a(n+1);
    for (int i = 0; i < n; i++) {
        a[i+1] = a[i] + (s[i]=='1');
    }
    ll res = 0;
    // similar trick r-l=t*(ar-al)  <=>   r-kar = l-kal
    for (int t = 1; t <= T; t++) {
        vector<ll> vals(n+1);
        for (int i = 0; i <= n; i++) {
            vals[i] = i - t*a[i];
        }
        sort(vals.begin(), vals.end());
        int i = 0;
        while (i <= n) {
            ll x = vals[i];
            ll cnt = 0;
            while (i<=n && vals[i]==x) {
                i++; cnt++;
            }
            res += cnt*(cnt-1)/2;
        }
    }

    // t>T
    vector<int> nxt(n+1);
    int las = n; nxt[n] = las;
    for (int i = n-1; i >= 0; i--) {
        if (s[i]=='1') las = i;
        nxt[i] = las;
    }
    for (int l = 0; l < n; l++) {
        int ones = 1;
        int rl = nxt[l];
        while (true) {
            if (rl == n) break;
            int rr = nxt[rl+1];
            int at_least = l + ones * (T+1);
            rl = max(rl, at_least-1);
            if (rl < rr) {
                int has = (rr-l)/ones - (rl-l)/ones;
                res += has;
            }
            if (rl >= n) break; // limit ones
            rl = rr; ones++;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
