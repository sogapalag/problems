#include <bits/stdc++.h>

using namespace std;


// distinct, if not, consideer 22727277
void solve() {
    int n, _;
    cin >> n >> _;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    map<int, int> cnt;
    int mi = 1e9+19;
    for (int x: a) {
        if (x > mi) cnt[x-mi]++;
        mi = min(mi, x);
    }
    int res = cnt.rbegin()->second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
