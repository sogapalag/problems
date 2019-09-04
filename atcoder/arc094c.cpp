#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a,a+3);
    int x=a[2]-a[1],y=a[2]-a[0];
    int res = (x+y+1)/2 + ((x+y)&1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
