#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    set<int> s;
    for (int i = 1; i*i <= n; i++) {
        int d = n/i;
        s.insert(d);
        if (d > 1) s.insert(n/(d-1));
        s.insert(n/d);
        s.insert(n/(d+1));
        s.insert(n/(d+2));
    }
    cout << s.size() << "\n";
    for (auto& x: s) {
        cout << x << ' ';
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
