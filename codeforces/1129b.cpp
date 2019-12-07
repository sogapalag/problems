#include <bits/stdc++.h>

using namespace std;


void solve() {
    int k; cin >> k;
    int d = 1;
    int x;
    for (; d < 2000; d++) {
        int f = d + d - (k%d);
        x = (k+f)/d + f;
        if (x <= 1e6) break;
    }

    vector<int> a(d+1);
    a[d] = x;
    int rem = k % d;
    for (int i = 0; i < rem; i++) {
        a[i] = -1;
    }
    for (int i = rem; i < d; i++) {
        a[i] = -2;
    }

    cout << d+1 << "\n";
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
