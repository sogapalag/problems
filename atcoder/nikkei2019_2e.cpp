#include <bits/stdc++.h>

using namespace std;

// by sum a+b <= sum c
// get YES iff 2*k- <= n-
// construction is first-half x with second-half y. z by parity.
// one can check initial hold by iff condition. then since x--,y--,z-=2, all holds.
void solve() {
    int n, k;
    cin >> n >> k;
    if (2*(k-1) > n-1) {
        cout << -1; return;
    }

    int x = k + (n-1)/2, y = k + 2*n-1, z = k + 3*n-1;
    while (x >= k) {
        cout << x << ' ' << y << ' ' << z << "\n";
        x--; y--; z-=2;
    }
    x = k + n-1; z = k + 3*n-2;
    while (y >= k+n) {
        cout << x << ' ' << y << ' ' << z << "\n";
        x--; y--; z-=2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
