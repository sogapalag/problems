#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

using ll=long long;

void solve() {
    int n, m, Q;
    cin >> n >> m >> Q;
    vector<int> cnt(m+1, 0);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<vector<int>> h(n+1);
    for (int i = 1; i <= m; i++) {
        h[cnt[i]].emplace_back(i);
    }
    vector<pair<ll,int>> q(Q);
    for (int i = 0; i < Q; i++) {
        ll k; cin >> k;
        q[i] = {k, i};
    }
    sort(q.begin(), q.end());
    vector<int> res(Q);

    Tree<int> t;
    ll sum = n;
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j: h[i]) {
            t.insert(j);
        }
        while (k < Q && q[k].first <= sum + (int)t.size()) {
            ll x; int id;
            tie (x, id) = q[k];
            res[id] = *t.find_by_order(x - sum - 1);
            k++;
        }
        sum += t.size();
    }
    assert(sum == (ll)n * m);
    while (k < Q) {
        ll x; int id;
        tie (x, id) = q[k];
        res[id] = (x - sum - 1) % m + 1;
        k++;
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
