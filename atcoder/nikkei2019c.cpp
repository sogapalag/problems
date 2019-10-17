#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Node& _oth) const {
        return x+y > _oth.x+_oth.y;
    }
};

// for pair swap, find x+y sortness.
// or vies as, base -(sum y). each select +(x+y)
void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end());
    ll res = 0;
    for (int i = 0; i < n; i++) {
        if (i&1) res -= a[i].y;
        else res += a[i].x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
