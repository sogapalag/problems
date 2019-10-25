#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    int i, x;
    Node() {}
    Node(int _i, int _x) : i(_i), x(_x) {}
    bool operator<(const Node& _oth) const {
        return i < _oth.i || (i == _oth.i && x > _oth.x);
    }
};

// x may not need sort, since eventually <= cnt+i. once in pq, cannot miss 
void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int k,x;
        cin >> k >> x;
        a[i] = {k, x};
    }
    sort(a.begin(), a.end());
    int cnt = 0;
    ll sum = 0;
    priority_queue<int,vector<int>, greater<int>> pq;
    for (int i = n-1; i >= 0; i--) {
        if (a[i].i <= cnt + i) {
            pq.push(a[i].x);
        } else {
            if (pq.empty() || a[i].x <= pq.top()) {
                sum += a[i].x;
            } else {
                sum += pq.top(); pq.pop();
                pq.push(a[i].x);
            }
            cnt++;
        }
    }
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
