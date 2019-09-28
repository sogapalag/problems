#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s,t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();

    vector<int> sum(n+1), tum(m+1);
    sum[0] = tum[0] = 0;
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + (s[i]-'A'+1);
    }
    for (int i = 0; i < m; i++) {
        tum[i+1] = tum[i] + (t[i]-'A'+1);
    }

    int q; cin >> q;
    while (q--) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        bool res = (sum[y]-sum[x-1]) % 3 == (tum[v]-tum[u-1]) % 3;
        cout << (res?"YES\n":"NO\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
