#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y,z;
    cin >> x >> y >> z;
    int m = max({x,y,z});
    int o = -m+x+y+z;
    cout << (o>=m-1?"Yes\n":"No\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
