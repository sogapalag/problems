#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Node& _oth) const {
        return x < _oth.x;
    }
};

void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        if(x>y) swap(x,y);
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    int lmi = a[0].x, lmx = a[n-1].x;
    int rmi = 0x3f3f3f3f, rmx = -1;
    for (int i = 0; i < n; i++) {
        rmi = min(rmi, a[i].y);
        rmx = max(rmx, a[i].y);
    }
    ll res = 1ll*(lmx-lmi) * (rmx-rmi);

    int coeff = (rmx-lmi);
    int ans = 0x3f3f3f3f;
    rmx = rmi = a[0].y;
    for (int i = 1; i < n-1; i++) {
        ans = min(ans, max(rmx, a[n-1].x) - min(rmi, a[i].x));
        rmx = max(rmx, a[i].y);
        rmi = min(rmi, a[i].y);
    }
    res = min(res, 1ll*ans*coeff);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
