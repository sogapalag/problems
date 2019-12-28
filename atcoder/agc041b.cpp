#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

void solve() {
    int n;
    ll m, v;
    int p;
    cin >> n >> m >> v >> p;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(),greater<ll>());
    
    auto ck = [&](int i){
        ll tot = m*v;
        const ll X = a[i] + m; tot -= m;
        int cnt = 0;
        vector<ll> reso;
        for (int j = 0; j < n; j++) {
            if (j!=i) {
                //if (tot <= 0) break;
                if (a[j] > X) {
                    ll dx = min(m, tot);
                    tot -= dx;
                    cnt++;
                } else {
                    ll dx = min({X-a[j], m, tot});
                    tot -= dx;
                    if (dx < m) {
                        reso.push_back(m - dx);
                    }
                }
            }
        }
        sort(reso.begin(), reso.end(), greater<ll>());
        int j = 0;
        while (tot > 0) {
            tot -= reso[j++];
            cnt++;
        }
        return cnt < p;
    };
    int res = bs_last<int>(0, n, ck);
    res++;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
