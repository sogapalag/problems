#include <bits/stdc++.h>

using namespace std;

using Point=array<int,3>;
using V = vector<int> ;
// match dup's other-dim sortness
void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    for (auto& p: a) {
        cin >> p[0] >> p[1] >> p[2];
    }

    function<int(V, int)> match = [&](V ids, int dim) {
        if (dim == 3) return ids[0];
        map<int,V> mp;
        for (int i: ids) {
            mp[a[i][dim]].emplace_back(i);
        }
        V rem;
        for (auto& p: mp) {
            int r = match(p.second, dim+1);
            if (r != -1) rem.emplace_back(r);
        }
        int n = rem.size();
        for (int i = 0; (i+1) < n; i+=2) {
            cout << rem[i]+1 << ' ' << rem[i+1]+1 << "\n";
        }
        return (n&1)?rem.back():-1;
    };
    V id(n);
    iota(id.begin(), id.end(), 0);
    match(id, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
