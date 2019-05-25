#include <bits/stdc++.h>

using namespace std;


void solve() {
    int r, D, x;
    cin >> r >> D >> x;
    auto f = [&](int x){return r*x-D;};
    for (int i = 0; i < 10; i++) {
        x = f(x);
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
