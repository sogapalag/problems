#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    sort(a.begin(), a.end());

    priority_queue<int> pq;
    ll sum = 0;
    ll res = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        int x = a[i].first;
        while (j < n && a[j].first == x) {
            pq.push(a[j].second);
            sum += a[j].second;
            j++;
        }
        
        // greedy let large t, move small step.
        // small t might advance to nx
        int nx = j<n ? a[j].first : 2e9;
        int z = x;
        while (!pq.empty() && z < nx) {
            res += pq.top() *1ll* (z-x);
            sum -= pq.top();
            pq.pop(); z++;
        }
        if (z == nx) {
            res += sum * 1ll * (z - x);
        }
        i = j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
