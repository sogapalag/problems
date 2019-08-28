#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
ll calc(ll x){
    ll res = 0;
    while (x) {
        res += x%10;
        x/=10;
    }
    return res;
}
bool cmp(ll x, ll y) {
    return x*calc(y) <= y*calc(x);
}
void solve() {
    int n; cin >> n;
    ll x=0, y=1;
    for (int _ = 0; _ < n; _++) {
        x += y;
        cout << x << "\n";
        while (cmp(x+10*y, x+y)) {
            y *= 10;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
