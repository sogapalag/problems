#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    string s; cin >> s;
    string t;
    for (int i = 0; i < k-1; i++) {
        t += "()";
    }
    int m = n/2 - (k-1);
    for (int _ = 0; _ < m; _++) {
        t += '(';
    }
    for (int _ = 0; _ < m; _++) {
        t += ')';
    }

    vector<pair<int, int>> res;
    // fit each pos
    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) {
            int j;
            for (j = i+1; j < n; j++) {
                if (s[j] == t[i]) break;
            }
            res.emplace_back(i+1, j+1);
            reverse(s.begin()+i, s.begin()+j+1);
        }
    }
    for (int i = 0; i < n; i++) {
        assert(s[i] == t[i]);
    }
    assert((int)res.size() <= n);

    cout << res.size() << "\n";
    for (auto& p: res) {
        cout << p.first << ' ' << p.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
