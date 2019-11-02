#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y;
    cin >> x >> y;
    int g = __gcd(x,y);
    cout << (g==1?"Finite":"Infinite") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
