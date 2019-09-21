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
        int tmp = p.second;
        if (cnt.find(p.first-1) != cnt.end()) tmp += cnt[p.first-1];
        if (cnt.find(p.first+1) != cnt.end()) tmp += cnt[p.first+1];
        res = max(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
