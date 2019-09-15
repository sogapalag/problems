#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s,t;
    cin >> s >> t;
    int cnt = 0;
    for (char x: s) if (x=='a') cnt++;
    for (char x: t) if (x=='a') cnt++;
    if (cnt&1) {
        cout << -1; return;
    }

    vector<int> ab, ba;
    for (int i = 0; i < n; i++) {
        if (s[i]=='a' && t[i]=='b') ab.emplace_back(i);
        if (s[i]=='b' && t[i]=='a') ba.emplace_back(i);
    }
    vector<pair<int, int>> res;
    while ((int)ab.size() >= 2) {
        int i = ab.back(); ab.pop_back();
        int j = ab.back(); ab.pop_back();
        res.emplace_back(i+1, j+1);
    }
    while ((int)ba.size() >= 2) {
        int i = ba.back(); ba.pop_back();
        int j = ba.back(); ba.pop_back();
        res.emplace_back(i+1, j+1);
    }
    if (!ab.empty()) {
        assert(!ba.empty());
        int i = ab[0];
        int j = ba[0];
        res.emplace_back(i+1, i+1);
        res.emplace_back(i+1, j+1);
    }
    cout << res.size() << "\n";
    for (auto& p: res) {
        int x,y;
        tie(x,y) = p;
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
