#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    vector<vector<char>> g(m);
    unordered_set<string> st;
    for (auto& x: s) {
        for (int i = 0; i < m; i++) {
            g[i].push_back(x[i]);
        }
        st.insert(x);
    }
    for (auto& a: g) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    // key brute-force, since no more than n
    function<bool(string)> dfs = [&](string t){
        int i = t.size();
        if (i == m) {
            if (st.find(t) == st.end()) {
                cout << t << '\n';
                return true;
            }
            return false;
        }
        for (char c:g[i]) {
            t.push_back(c);
            if (dfs(t)) return true;
            t.pop_back();
        }
        return false;
    };
    if (!dfs("")) cout << "-\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
