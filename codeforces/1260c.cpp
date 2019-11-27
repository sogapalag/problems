#include <bits/stdc++.h>

using namespace std;


void solve() {
    int r,b,k;
    cin >> r >> b >> k;
    int g = __gcd(r,b);
    r/=g; b/=g;
    if (r > b) swap(r, b);

    int x = r==1?b-1:  (b-1+r-1)/r;
    // not b/r
    // r buckets, since b-1 points fall into, must one bucket has ceil{ (b-1)/r }
    cout << ((x<k)?"OBEY\n":"REBEL\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    //cout << endl;
}
