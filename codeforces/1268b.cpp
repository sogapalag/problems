#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// color white black alternate, classic.
// '<=', after remove equal length(row or col)
//  remain form 1,2,...,k. then (1,1,3,3,...) will simply achieve upper bound.
void solve() {
    int n; cin >> n;
    ll w = 0, b = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        w += x/2;
        b += (x+1)/2;
        swap(w,b);
    }
    cout << min(w,b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
