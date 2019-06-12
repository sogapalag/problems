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
using ll=long long;

// each row, ll...lrr...r, bi's l, (X-bi)'s r,
// optimal, pick k=qX+rem, q full row, iter remain in each row.
void solve() {
    int n, X;
    cin >> n >> X;
    vector<int> b(n);
    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i] >> l[i] >> r[i];
    }
    ll B = 0;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        B += 1ll*l[i]*b[i];
        a[i] = 1ll*l[i]*b[i] + 1ll*(X-b[i])*r[i];
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int x, int y){
            return a[x] > a[y];
            });
    vector<long long> cum(n);
    ll tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += a[id[i]];
        cum[i] = tmp;
    }
    ll res = bs_first<ll>(0, 1ll*n*X+1, [&](ll k){
            if (!k) return 0 >= B;
            int q = k/X, rem = k%X;
            if (rem == 0) return cum[q-1] >= B;
            ll res = 0;
            for (int i = 0; i < n; i++) {
                int j = id[i];
                ll tmp = 0;
                tmp += 1ll*l[j]*min(rem, b[j]) + 1ll*r[j]*max(0, rem-b[j]);
                if (q) {
                    if (i < q) {
                        tmp += cum[q] - a[j];
                    } else {
                        tmp += cum[q-1];
                    }
                }
                res = max(res, tmp);
            }
            return res >= B;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
