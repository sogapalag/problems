#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    ll best = 0; // put O between, #J x #I
    vector<int> J(n + 1), I(n + 1);
    for (int i = 0; i < n; i++) {
        J[i+1] = J[i] + (s[i]=='J');
        I[i+1] = I[i] + (s[i]=='I');
    }
    ll res = 0;
    ll x = 0, y = 0; // put J begin; put I end
    for (int i = 0; i < n; i++) {
        best = max(best, J[i]*1ll*(I[n]-I[i]));
        if (s[i] == 'O') {
            res += J[i]*1ll*(I[n]-I[i]);
            x += I[n] - I[i];
            y += J[i];
        }
    }
    best = max({best,x,y});
    res += best;
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
