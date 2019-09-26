#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

void solve() {
    int n; cin >> n;
    vector<int> a(3*n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> L(n+1), R(n+1);
    L[0] = 0;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int i = 0; i < n; i++) {
        L[0] += a[i];
        min_heap.push(a[i]);
    }
    for (int i = 0; i < n; i++) {
        L[i+1] = L[i] + a[i+n];
        min_heap.push(a[i+n]);
        L[i+1] -= min_heap.top();
        min_heap.pop();
    }

    R[n] = 0;
    priority_queue<int> max_heap;
    for (int i = 0; i < n; i++) {
        R[n] += a[i+2*n];
        max_heap.push(a[i+2*n]);
    }
    for (int i = n-1; i >= 0; i--) {
        R[i] = R[i+1] + a[i+n];
        max_heap.push(a[i+n]);
        R[i] -= max_heap.top();
        max_heap.pop();
    }

    ll res = -(1ll<<60);
    for (int i = 0; i <= n; i++) {
        res = max(res, L[i]-R[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
