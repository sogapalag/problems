#include <bits/stdc++.h>

using namespace std;


// calc reversly, i.e. edge inc.
// find for [0-i]'s left vals match. for graph g, although left-right diff nodes. but since will only maintain l->r edges, doesn't need reindex node.
// key part is dfs, although only one-layer, those flag check, can ensure, new l, may update befores' match.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    int q; cin >> q;
    vector<bool> is_del(n, false);
    vector<int> qry(q);
    for (auto& x: qry) {
        cin >> x; x--;
        is_del[x] = true;
    }
    vector<vector<int>> g(m+1);
    for (int i = 0; i < n; i++) {
        if (!is_del[i]) {
            int p, c;
            tie(p, c) = a[i];
            if (p <= m)
                g[p].emplace_back(c);
        }
    }
    vector<bool> trk(m+1, false);
    vector<int> left(m+1, -1);
    function<bool(int)> dfs = [&](int l){
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    };
    vector<int> res(q);
    int take = 0;
    for (int i = q-1; i >= 0; i--) {
        fill(trk.begin(), trk.end(), false);
        while (dfs(take)) {
            fill(trk.begin(), trk.end(), false);
            take++;
        }
        res[i] = take;
        int p, c;
        tie(p, c) = a[qry[i]];
        if (p <= m)
            g[p].emplace_back(c);
    }
    for (auto& x: res) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
