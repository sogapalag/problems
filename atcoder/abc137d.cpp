#include <bits/stdc++.h>

using namespace std;

struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].x = k - a[i].x;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return u.x > v.x;
    });
    int res = 0;
    int j = 0;
    priority_queue<int> pq;
    for (int i = k-1; i >= 0; i--) {
        while (j < n && a[j].x >= i) {
            pq.push(a[j++].y);
        }
        if (!pq.empty()) {
            res += pq.top();
            pq.pop();
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
