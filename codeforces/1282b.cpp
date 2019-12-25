#include <bits/stdc++.h>

using namespace std;

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
    int n,p,k;
    cin >> n >> p >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());

    vector<int> pref(n+1), sum(n+1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i-1]+a[i-1];
        if(i-k>=0) sum[i] = sum[i-k] + a[i-1];
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (sum[i] <= p) {
            int tmp = i/k * k;
            int x = p-sum[i];
            int j = i%k;
            int y = bs_last<int>(0, j+1, [&](int y){
                    return pref[y] <= x;
                    });
            tmp += y;
            res = max(res, tmp);
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
