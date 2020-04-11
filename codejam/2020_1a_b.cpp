#include <bits/stdc++.h>

using namespace std;

const int L = 31; 
// each row 2^i
void solve() {
    int n; cin >> n;
    cout << "\n";
    if (n < 500) {
        for (int i = 1; i <= n; i++) {
            cout << i << " 1\n";
        }
        return;
    }
    int left = 1;
    int x = n-L;
    int w = 0;
    for (int i = 0; i < L; i++) {
        if (x>>i&1) {
            if (left) {
                for (int j = 0; j <= i; j++) {
                    cout << i+1 << ' ' << j+1 << '\n';
                }
            } else {
                for (int j = i; j >= 0; j--) {
                    cout << i+1 << ' ' << j+1 << '\n';
                }
            }
            left ^= 1;
            continue;
        }
        w++;
        if (left) {
            cout << i+1 << " 1\n";
        } else {
            cout << i+1 << ' ' << i+1 << '\n';
        }
    }
    for (int i = L; i < L+(L-w); i++) {
        int j = (left ? 0 : i);
        cout << i+1 << ' '  << j+1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
