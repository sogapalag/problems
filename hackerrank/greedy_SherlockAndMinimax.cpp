#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();
    int p, q;
    cin >> p >> q;
    vector<pair<int, int>> cdi;
    // check whether mid covered
    for (int i = 1; i < n; i++) {
        if ((a[i] - a[i-1])&1) {
            int x = (a[i]-a[i-1])/2;
            if (p <= a[i-1]+x && a[i-1]+x <= q)
                cdi.emplace_back(x, a[i-1]+x);
            if (p <= a[i]-x && a[i]-x <= q)
                cdi.emplace_back(x, a[i]-x);
        } else {
            int x = (a[i]-a[i-1])/2;
            if (p <= a[i-1]+x && a[i-1]+x <= q)
                cdi.emplace_back(x, a[i-1]+x);
        }
    }
    // check board p/q
    int i = lower_bound(a.begin(), a.end(), p) - a.begin();
    if (i == 0)
        cdi.emplace_back(a[0]-p, p);
    else if (i<n && p >= (a[i]+a[i-1])/2)
        cdi.emplace_back(a[i]-p, p);
    i = lower_bound(a.begin(), a.end(), q) - a.begin();
    if (i == n)
        cdi.emplace_back(q-a[n-1], q);
    else if (i>0 && q <= (a[i]+a[i-1])/2)
        cdi.emplace_back(q-a[i-1], q);
    sort(cdi.begin(), cdi.end(), [&](auto& u, auto& v){
            return u.first > v.first || (u.first==v.first && u.second < v.second);
            });
    int res = cdi[0].second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
