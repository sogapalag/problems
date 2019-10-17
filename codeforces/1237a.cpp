#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int cnt = 0;
    for (auto& x: a) {
        cin >> x;
        if (x & 1) cnt++;
    }
    int up = 0;
    cnt /= 2;
    for (auto& x: a) {
        if (x & 1) {
            x = x<0? (x/2-1):x/2;
            if (up < cnt) {
                x++; up++;
            }
        } else x /= 2;
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
