#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    map<int, int> cnt;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    int res = 0;
    for (auto& p: cnt) {
        if (p.second & 1) res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
