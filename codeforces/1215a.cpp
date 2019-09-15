#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a,b;
    cin >> a >> b;
    int x,y;
    cin >> x >> y;
    int n; cin >> n;
    if (x > y) {
        swap(a,b);
        swap(x,y);
    }
    int t = min(n/x, a);
    int mx = t + min((n-t*x)/y, b);
    int mi = max(0, n - (x-1)*a - (y-1)*b);
    cout << mi << ' ' << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
