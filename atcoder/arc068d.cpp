#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    set<int> s;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        s.insert(x);
    }
    int res = s.size();
    if ((n-s.size())&1) res--;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
