#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> cnt(26, 0);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        cnt[s[0] - 'a']++;
    }
    int res = 0;
    for (auto& x: cnt) {
        if (x > 1){
            int t = x/2;
            int k = x - t;
            res += t * (t-1) /2;
            res += k * (k-1) /2;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
