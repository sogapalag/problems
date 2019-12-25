#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a,b,c,r;
    cin >> a >> b >> c >> r;
    if (a>b)swap(a,b);
    int d = b-a;
    int x = c-r, y = c+r;
    x = max(x, a);
    y = min(y, b);
    if (x <= y) {
        d -= y-x;
    }
    cout << d << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
