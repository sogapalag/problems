#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int res = bs_first<int>(0, m, [&](int x){
            int crt = 0;
            for (int l: a) {
                int r = l + x;
                if (crt > l) {
                    if (crt > r) return false;
                } else {
                    if (crt > r-m) {
                        crt = l;
                    }
                }
            }
            return true;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
