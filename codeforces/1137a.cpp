#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

int a[1024][1024];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Tree<int>> row(n), col(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i][j] = x;
            row[i].insert(x);
            col[j].insert(x);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = a[i][j];
            int r = row[i].order_of_key(x), rsz = row[i].size();
            int c = col[j].order_of_key(x), csz = col[j].size();
            x = max(r, c);
            int res = max(rsz + x - r, csz + x - c);
            cout << res << ' ';
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
