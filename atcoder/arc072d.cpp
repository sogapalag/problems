#include <bits/stdc++.h>

using namespace std;
using ll=long long;


void solve() {
    ll x,y;
    cin >> x >> y;
    if (x<y) swap(x,y);
    bool res;
    res = x-y>1;
    cout << (res?"Alice":"Brown");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
