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

// 1. note consective rot has cum property
// 2. since rot square inside dec. after ith rot, iff still in the square.
void solve() {
    int n; cin >> n;
    int m; cin >> m;
    vector<int> a(m+1);
    vector<int> b(m+1);
    vector<int> d(m+1);
    vector<int> D(m+1); // a-b
    vector<int> S(m+1); // a+b+d
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> d[i];
        D[i] = a[i] - b[i];
        S[i] = a[i] + b[i] + d[i];
    }
    vector<ll> F(m+1); // x1 = D1 + y0
    vector<ll> G(m+1); // y1 = S1 - x0
    F[0] = G[0] = 0;
    for (int i = 1; i <= m; i++) {
        F[i] = D[i] + G[i-1];
        G[i] = S[i] - F[i-1];
    }
    auto rot = [&](int i, int x, int y) -> pair<ll,ll>{
        ll u = F[i], v = G[i];
        if (i%4 == 0) {
            u += x; v += y;
        } else if (i%4 == 1) {
            u += y; v -= x;
        } else if (i%4 == 2) {
            u -= x; v -= y;
        } else if (i%4 == 3) {
            u -= y; v += x;
        }
        return {u, v};
    };
    int q; cin >> q;
    while (q--) {
        ll w; cin >> w;
        int x = w/n, y = w%n;
        x++; y++;
        int i = bs_last<int>(1, m+1, [&](int i){
                ll u, v;
                tie(u, v) = rot(i, x, y);
                return a[i] <= u && u <= a[i]+d[i] && b[i] <= v && v <= b[i]+d[i];
                });
        tie(x, y) = rot(i, x, y);
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
