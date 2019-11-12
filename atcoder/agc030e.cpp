#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s,t;
    cin >> s >> t;
    auto get_cut = [&](auto& s){
        vector<int> cut;
        char las = '0';
        for (int i = 0; i < n; i++) {
            if (s[i] != las) {
                cut.emplace_back(i);
            }
            las = s[i];
        }
        return cut;
    };
    auto a = get_cut(s);
    auto b = get_cut(t);
    // normalize to same even size.
    while (a.size() < b.size()) {
        a.emplace_back(n);
    }
    while (b.size() < a.size()) {
        b.emplace_back(n);
    }
    if (a.size()&1) {
        a.emplace_back(n);
        b.emplace_back(n);
    }
    int m = a.size();
    int mi = 1<<30;
    // a[i] match b[i+l]
    for (int l = -m; l <= m; l+=2) { // pairty must match
        int r = l+m;
        int d = 0;
        for (int i = 0; i+r < m; i++) {
            d += a[i];
        }
        for (int i = m-l; i < m; i++) {
            d += n - a[i];
        }
        for (int j = 0; j < l; j++) {
            d += b[j];
        }
        for (int j = r; j < m; j++) {
            d += n - b[j];
        }
        for (int i = 0; i < m; i++) {
            if (0 <= i+l && i+l < m) {
                d += abs(a[i] - b[i+l]);
            }
        }
        mi = min(mi, d);
    }
    cout << mi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
