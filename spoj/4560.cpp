#include <bits/stdc++.h>

using namespace std;


void solve() {
    while (true) {
        int n; cin >> n;
        if (!n) return;
        const int VIT = 1e8; 
        vector<int> a(n+2);
        a[0] = -VIT; a[n+1] = VIT;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int m; cin >> m;
        vector<int> b(m+2);
        b[0] = -VIT; b[m+1] = VIT;
        for (int i = 1; i <= m; i++) {
            cin >> b[i];
        }
        vector<int> cum_a(n+2);
        cum_a[0] = 0;
        for (int i = 1; i <= n; i++) {
            cum_a[i] = cum_a[i-1] + a[i];
        }
        cum_a[n+1] = cum_a[n];
        vector<int> cum_b(m+2);
        cum_b[0] = 0;
        for (int i = 1; i <= m; i++) {
            cum_b[i] = cum_b[i-1] + b[i];
        }
        cum_b[m+1] = cum_b[m];
        int la = 0, lb = 0;
        int res = 0;
        for (int i = 1; i <= n+1; i++) {
            if (binary_search(b.begin(), b.end(), a[i])){
                int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
                res += max(cum_a[i] - cum_a[la], cum_b[j] - cum_b[lb]);
                la = i; lb = j;
            }
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
