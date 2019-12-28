#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n,a,b;
    cin >> n >> a >> b;
    if ((b-a)%2==0) {
        cout << (b-a)/2;
    } else {
        ll res = (b-a)/2;
        res += min(a, n-b+1);
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
