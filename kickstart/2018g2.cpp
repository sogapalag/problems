#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(n+1);
    int a1, b1, c1, m1;
    cin >> x[1] >> x[2] >> a1 >> b1 >> c1 >> m1;
    vector<int> y(n+1);
    int a2, b2, c2, m2;
    cin >> y[1] >> y[2] >> a2 >> b2 >> c2 >> m2;
    for (int i = 3; i <= n; i++) {
        x[i] = (1ll*a1*x[i-1] + 1ll*b1*x[i-2] + c1) % m1;
        y[i] = (1ll*a2*y[i-1] + 1ll*b2*y[i-2] + c2) % m2;
    }
    map<int, int> R;
    for (int i = 1; i <= n; i++) {
        int l = min(x[i], y[i]);
        int r = max(x[i], y[i]) + 1;
        R[l]--;
        R[r]++;
    }
    struct Node {
        int r, l, k;
        Node(int _r, int _l, int _k) : r(_r), l(_l), k(_k) {}
    };
    vector<Node> v; v.reserve(2*n);
    int cnt = 0;
    int cr = 1e9+1111;
    int cl;
    for (auto rit = R.crbegin(); rit != R.crend(); rit++) {
        cl = rit->first;
        if (cnt) {
            v.push_back(Node(cr, cl, cnt));
        }
        cnt += rit->second;
        cr = cl;
    }
    int sz = v.size();
    vector<long long> cum(sz+1);
    cum[0] = 0;
    for (int i = 1; i <= sz; i++) {
        cum[i] = cum[i-1] + 1ll*v[i-1].k*(v[i-1].r - v[i-1].l);
    }
    vector<int> z(q+5);
    int a3, b3, c3, m3;
    cin >> z[1] >> z[2] >> a3 >> b3 >> c3 >> m3;
    for (int i = 3; i <= q; i++) {
        z[i] = (1ll*a3*z[i-1] + 1ll*b3*z[i-2] + c3) % m3;
    }
    long long res = 0;
    for (int i = 1; i <= q; i++) {
        long long k = z[i] + 1;
        int j = lower_bound(cum.begin(), cum.end(), k) - cum.begin();
        if (j <= sz) {
            k -= cum[--j];
            res += 1ll * i * (v[j].r - (k-1)/v[j].k);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
