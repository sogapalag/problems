#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a,b,c,x,y;
    cin >> a >> b >> c;
    cin >> x >> y;
    int res = 0;
    if (2*c < a + b) {
        int z = min(x,y);
        res += z * 2*c;
        x-=z; y-=z;
    }
    res += x*min(a,2*c)+y*min(b,2*c);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
