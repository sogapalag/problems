#include <bits/stdc++.h>

using namespace std;
using ll=long long;
bool ispref(string p, string s) {
    if (p.size() > s.size()) return false;
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i]!=s[i]) return false;
    }
    return true;
}
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(m);
    for (auto& x: s) cin >> x;
    vector<string> a;
    for (int i = 0; i < m; i++) {
        bool ok = true;
        for (int j = 0; j < m; j++)if(j!=i) {
            if (ispref(s[j], s[i])) {
                ok = false; break;
            }
        }
        if (ok) a.push_back(s[i]);
    }
    ll res = 1ll<<n;
    for (auto& _: a) {
        m = _.size();
        res -= 1ll<<(n-m);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
