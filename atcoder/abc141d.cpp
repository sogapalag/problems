#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    priority_queue<int> pq;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        pq.push(x);
    }
    while (m--) {
        int x = pq.top(); pq.pop();
        x/=2; pq.push(x);
    }
    long long sum = 0;
    while (!pq.empty()) {
        sum += pq.top();
        pq.pop();
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
