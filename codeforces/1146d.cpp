#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int m,a,b;
    cin >> m >> a >> b;
    vector<int> least(a + b, -1); // least[x] := required m, s.t. can reach x.
    int x = 0, r = 0;
    while (true) {
        least[x] = r;
        if (x >= b) x -= b;
        else x += a;
        if (x == 0) break;
        r = max(r, x);
    }
    ll res = 0;
    for (int i = 0; i < a+b; i++) {
        if (least[i] != -1) {
            res += max(0, m - least[i] + 1);
        }
    }
    // for large x, least[x] = x iff g|x
    // so arithmetric l, l-g, ... r
    if (m >= a+b) {
        int g = __gcd(a,b);
        int l = m-(a+b)+1;
        int r = l - (l/g*g);
        res += ((l-r)/g + 1)*1ll*(l+r)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
