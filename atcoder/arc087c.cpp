#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    map<int, int> mp;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        mp[x]++;
    }
    int res = 0;
    for (auto& p: mp) {
        int x,y;
        tie(x,y) = p;
        if (x <= y) res += y-x;
        else res += y;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
