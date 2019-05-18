#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

void solve() {
    int t; cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        vector<int> a(n);
        for (auto& x: a) {
            cin >> x;
        }
        sort(a.begin(), a.end());
        const int N = 1e9+10; 
        int res = bs_last<int>(0, N, [&](int x){
                int cnt = c;
                int z = a[0];
                auto it = a.begin() + 1;
                cnt--;
                while (cnt--) {
                    it = lower_bound(it, a.end(), z+x);
                    if (it == a.end()) return false;
                    z = *it;// after it should ++, but AC, might x!=0
                }
                return true;
            });
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
