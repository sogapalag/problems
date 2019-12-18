#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int x, y; ll z;
    Node() {}
    Node(int _x, int _y, ll _z) : x(_x), y(_y), z(_z) {}
};
// consider i will pay or get
// sum total, into two groups.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        a[x] += z;
        a[y] -= z;
    }
    vector<int> pos, neg;
    for (int i = 0; i < n; i++) {
        if (a[i]>0) pos.push_back(i);
        if (a[i]<0) neg.push_back(i);
    }

    vector<Node> res;
    n = pos.size();
    m = neg.size();
    int i = 0, j = 0;
    while (i<n && j<m) {
        ll z = min(a[pos[i]], -a[neg[j]]);
        res.emplace_back(pos[i], neg[j], z);
        a[pos[i]] -= z;
        a[neg[j]] += z;
        if (a[pos[i]] == 0) i++;
        if (a[neg[j]] == 0) j++;
    }

    cout << res.size() << "\n";
    for (auto& r: res) {
        cout << r.x+1<< ' '<< r.y+1<<' '<< r.z<<'\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
