#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y,n;
    cin >> x >> y >> n;
    int cnt=0;
    for (int i = 0; i <= n; i++) {
        if (x>=i && y>=(n-i)) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
