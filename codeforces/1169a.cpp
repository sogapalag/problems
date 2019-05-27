#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, a, x, b, y;
    cin >> n >> a >> x >> b >> y;
    a--, x--, b--, y--;
    
    for (int i = 1; i <= n; i++) {
        a = (a+1)%n;
        b = (b-1+n)%n;
        if (a==b) {
            cout << "YES"; return;
        }
        if (a==x || b==y) break;
    }
    cout << "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
