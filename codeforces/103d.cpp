#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int B = 512; 

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int q; cin >> q;
    vector<vector<pair<int,int>>> qrs(n+1);
    for (int _ = 0; _ < q; _++) {
        int x,y;
        cin >> x >> y;
        qrs[y].emplace_back(x, _);
    }
    vector<ll> res(q);

    for (int m = 1; m <= n; m++) {
        if (m < B) {
            vector<ll> sum(n+1);
            for (int i = 1; i <= n; i++) {
                sum[i] = (i>=m ? sum[i-m] : 0) + a[i-1];
            }
            for (auto& _: qrs[m]) {
                int x,i;
                tie(x,i) = _;
                res[i] -= (x>=m ? sum[x-m] : 0);
                int last = n/m*m + (x%m);
                if (last > n) last -= m;
                res[i] += sum[last];
            }
        } else {
            for (auto& _: qrs[m]) {
                int x,i;
                tie(x,i) = _;
                x--;
                for (int y = x; y < n; y+=m) {
                    res[i] += a[y];
                }
            }
        }
    }
    for (auto& x: res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
