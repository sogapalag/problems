#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pl=pair<ll,ll>;
// greedy sats. left. store current energy, till x+D release
void solve() {
    int n; ll D, A;
    cin >> n >> D >> A;

    priority_queue<pl,vector<pl>, greater<>> pq;
    for (int _ = 0; _ < n; _++) {
        ll x,h;
        cin >> x >> h;
        pq.emplace(x, h);
    }
    D = 2*D + 1;
    ll res = 0;
    ll E = 0;
    while (!pq.empty()) {
        ll x,h;
        tie(x,h) = pq.top(); pq.pop();
        if (h < 0) E += h;
        else if (E < h){
            ll k = (h - E + A-1)/A;
            res += k;
            E += k*A;
            pq.emplace(x + D, -k*A);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
