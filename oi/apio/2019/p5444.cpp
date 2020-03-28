#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n; ll A, B;
    cin >> n >> A >> B;
    if ((double)A*B/__gcd(A,B+1) >= INF) {
        ll res = 0;
        for (int _ = 0; _ < n; _++) {
            ll x, y;
            cin >> x >> y;
            res += y-x+1;
        }
        cout << res;
        return;
    }
    ll p = A/__gcd(A,B+1)*B; // not A*B (86pts...), p is already period
    // can easy to verify.
    // rigorous proof, simplify formula x(t1) = x(t2=t1+kB) (mod A)
    vector<pair<ll,int>> a;
    for (int _ = 0; _ < n; _++) {
        ll x,y;
        cin >> x >> y;
        y++;
        if (y-x >= p) {
            cout << p; return;
        }
        x %= p, y %= p;
        if (x < y) {
            a.emplace_back(x, +1);
            a.emplace_back(y, -1);
        } else {
            a.emplace_back(x, +1);
            a.emplace_back(p, -1);
            if (y > 0) {
                a.emplace_back(0, +1);
                a.emplace_back(y, -1);
            }
        }
    }
    sort(a.begin(), a.end());
    ll res = 0, l;
    int cnt = 0;
    for (auto& _: a) {
        ll r;int i;
        tie(r,i) = _;
        if (cnt == 0) {
            l = r;
        }
        cnt += i;
        if (cnt == 0) {
            res += r-l;
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
