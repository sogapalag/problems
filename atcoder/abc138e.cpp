#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s, t;
    cin >> s >> t;
    vector<int> cns(26,0), cnt(26,0);
    for (char x: s) {
        cns[x-'a']++;
    }
    for (char x: t) {
        cnt[x-'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] && !cns[i]) {
            cout << -1; return;
        }
    }
    int n = s.size(), m = t.size();
    vector<vector<int>> g(26);
    for (int i = 0; i < n; i++) {
        g[s[i]-'a'].emplace_back(i);
    }
    using ll=long long ;
    ll crt = -1;
    for (char x: t) {
        int k = x - 'a';
        ll nex = (crt+1)%n;
        int i = lower_bound(g[k].begin(), g[k].end(), nex) - g[k].begin();
        ll ad = i == (int)g[k].size()? (n + g[k][0] - nex+1) :g[k][i] - nex+1;
        crt += ad;
    }
    cout << crt+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
