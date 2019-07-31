#include <bits/stdc++.h>

using namespace std;


void solve() {
    double h, l;
    cin >> h >> l;
    double d = (l*l/h/2-h/2);
    cout << fixed << setprecision(9) << d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
