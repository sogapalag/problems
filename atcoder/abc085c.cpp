#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, Y;
    cin >> n >> Y;
    Y /= 1000;
    Y -= n;
    auto gg = [](){
        cout << "-1 -1 -1\n";exit(0);
    };
    if (Y < 0 || Y > 9*n) {
        gg();
    }
    int lim = Y/9;
    for (int z = 0; z <= lim; z++) {
        int y = (Y - 9*z)/4;
        if (4*y+9*z != Y) continue;
        int x = n-y-z;
        if (x<0 || y<0 || z<0) continue;
        cout << z <<' '<<y<<' '<<x; return;
    }
    gg();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
