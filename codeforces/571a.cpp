#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int a,b,c,n;
    cin >> a >> b >> c >> n;
    ll sum = 0;
    auto f = [&](ll x){
        if (x < 0) return 0ll;
        return (x+2)*(x+1)/2;
    };
    for (int x:{a,b,c}) {
        int z = a+b+c - x;
        // #z' <= x'
        for (int dx = 0; dx <= n; dx++) {
            int dz = min(x+dx - z, n-dx);
            sum += f(dz);
        }
    }
    ll tot = 1ll*(n+3)*(n+2)*(n+1)/6; // sum-on (r+k,k), or da+da+dc+dummy=n, i.e. z(n,4)
    cout << tot-sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
