#include <bits/stdc++.h>

using namespace std;


// code is easy, but need some thinking.
// first n odd -1, since 0, n-1 all has one-self-loop, and both can by n/2.
// for even, first pair 2*i, 2*i+1 up. call the graph D.
//  note any v of D, indeg[v]=outdeg[v]=2, i.e. \E euler.
//  and this euler of D <=> hami of original G.
// treat v of G denote edge of D.
void solve() {
    int n; cin >> n;
    if (n&1) {
        cout << -1; return;
    }
    vector<bool> trk(n);
    vector<int> euler;
    function<void(int)> dfs = [&](int u){
        if(trk[u])return;
        trk[u] = 1;
        dfs((u<<1)%n); dfs((u<<1|1)%n);
        euler.push_back(u);
    };
    dfs(0);
    reverse(euler.begin(), euler.end()); euler.push_back(0);
    for (auto& x: euler) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
