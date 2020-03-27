#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pi=pair<ll, int>;
// huffman, with min depth
void solve() {
    int n,k;
    cin >> n >> k;
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        pq.emplace(x, 0);
    }
    {// must add dummy
        int r = (n-1)%(k-1);
        if(r!=0) {
            for (int _ = 0; _ < k-1-r; _++) {
                pq.emplace(0, 0);
            }
        }
    }
    ll sum = 0;
    while (pq.size() > 1) {
        ll tmp = 0;
        int depth = 0;
        for (int _ = 0; _ < k; _++) {
            ll x;int d;
            tie(x,d) = pq.top(); pq.pop();
            tmp += x;
            depth = max(depth, d);
        }
        sum += tmp;
        pq.emplace(tmp, depth+1);
    }
    int d = pq.top().second;
    cout << sum << "\n";
    cout << d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
