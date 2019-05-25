#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a, b;
    cin >> a >> b;
    if (a>=6 && a<= 12) {
        b/=2;
    }
    if (a < 6) b =0;
    cout << b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
