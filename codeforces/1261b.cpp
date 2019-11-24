#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

// greedy pick largest x, min i to construct k-array. offline query
void solve() {
    int n; cin >> n;
    priority_queue<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pq.push({x, -i});
    }
    int m; cin >> m;
    vector<vector<pair<int,int>>> g(n+1);
    for (int i = 0; i < m; i++) {
        int k, pos;
        cin >> k >> pos;
        g[k].emplace_back(pos-1, i);
    }

    Tree<pair<int,int>> tree;
    vector<int> res(m);
    for (int k = 1; k <= n; k++) {
        int x,i;
        tie(x,i) = pq.top(); pq.pop();
        i = -i;
        tree.insert({i, x});

        for (auto& p: g[k]) {
            int pos, i;
            tie(pos, i) = p;
            res[i] = tree.find_by_order(pos)->second;
        }
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
