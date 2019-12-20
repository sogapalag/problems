#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,p;
    cin >> n >> p; // p is prime
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i]={x,y};
    }
    double res = 0;
    auto notd = [&](auto& _){
        int x,y;
        tie(x,y) = _;
        return (y-x+1) - (y/p - (x-1)/p);
    };
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        double tot = double(a[i].second-a[i].first+1) * (a[j].second-a[j].first+1);
        double exl = double(notd(a[i])) * notd(a[j]);
        res += (1-exl/tot) * 1000 * 2;
    }
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
