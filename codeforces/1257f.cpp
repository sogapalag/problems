#include <bits/stdc++.h>

using namespace std;


// split hi/lo part, iter each msk
// b similar <=> delta of hi/lo are dual
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    unordered_map<uint64_t, int> mp;
    auto hsh = [](const vector<int>& v){
        uint64_t h = 0;
        for (auto& x: v) {
            h = h*31 + x;
        }
        return h;
    };
    const int MSK = 1<<15;
    const int LO = MSK-1; 
    const int HI = (MSK-1)<<15; 
    for (int _ = 0; _ < MSK; _++) {
        int hi = _<<15;
        vector<int> delta(n);
        for (int i = 0; i < n; i++) {
            delta[i] = __builtin_popcount(hi ^ (a[i]&HI));
        }
        int z = *min_element(delta.begin(), delta.end());
        for (auto& x: delta) {
            x -= z;
        }
        mp[hsh(delta)] = hi;
    }
    for (int lo = 0; lo < MSK; lo++) {
        vector<int> delta(n);
        for (int i = 0; i < n; i++) {
            delta[i] = __builtin_popcount(lo ^ (a[i]&LO));
        }
        int z = *max_element(delta.begin(), delta.end());
        for (auto& x: delta) {
            x = z - x;
        }
        uint64_t h = hsh(delta);
        if (mp.find(h) != mp.end()) {
            int res = mp[h] + lo;
            cout << res; return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
