#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    if (n >= 1 && n == (n&-n)) {
        cout << "No"; return;
    }
    cout << "Yes\n";
    auto p = [](int x, int y){
        cout << x << ' ' << y << "\n";
    };
    p(n+1,n+2); p(n+2, 3); p(3, 1); p(1, 2); p(2, n+3);
    for (int x = 4; x+1 <= n; x+=2) {
        p(x, 1); p(1, x+1);
        p(x, n+x+1); p(x+1, n+x);
    }
    if (n%2 == 0) {
        int x = 1 << (31-__builtin_clz(n));
        int y = n^x;
        y^=1;
        p(x, n); p(y,n+n);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
