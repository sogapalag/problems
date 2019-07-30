#include <bits/stdc++.h>

using namespace std;


// the problem is like 001001..01000
// find longest length contain even 1s.
// so possible candidate, if 1s even, n.
// or odd, (i:], [0,j), where i, j are left/right-most 1's pos.
void solve() {
    int n, q;
    cin >> n >> q;
    set<int> pos;
    auto odd = [](int x)->bool{
        return __builtin_popcount(x)&1;
    };
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (odd(x)) pos.insert(i);
    }
    while (q--) {
        int p, v;
        cin >> p >> v;
        if (odd(v)) pos.insert(p);
        else pos.erase(p);

        if (pos.size() & 1) {
            int a = n-1 - *pos.begin();
            int b = *pos.rbegin();
            cout << max(a,b) << " ";
        } else {
            cout << n << " ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
