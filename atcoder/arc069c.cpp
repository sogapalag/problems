#include <bits/stdc++.h>

using namespace std;

using ll=long long;
void solve() {
    ll n,m;
    cin >> n >> m;
    ll res = min(n, m/2);
    m -= res*2;
    res += m/4;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
