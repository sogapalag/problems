#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int x, y, z;
    Node() {}
    Node(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    bool operator<(const Node& _oth) const {
        return y > _oth.y;
    }
};

// any used loan don't spend its p.z should be sorted by y
void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        a[i] = {x,y,z};
    }
    sort(a.begin(), a.end());
    vector<ll> dp(n+1);
    for (auto& p: a) {
        for (int i = n-1; i >= 0; i--) {
            // p as last i to loan
            dp[i+1] = max(dp[i+1], dp[i] + p.x - (ll)p.y*i);
            // put p as last n to loan, i.e. dp[i] don't +1, future loan could insert
            dp[i] = max(dp[i], dp[i] + p.x - (ll)p.y*p.z);
        }
    }
    cout << *max_element(dp.begin(), dp.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
