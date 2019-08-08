#include <bits/stdc++.h>

using namespace std;

template <typename T=double>
pair<T,T> ternary(T l, T r, function<T(T)> f, bool V=true) {
    int round = 400;
    while (round--) {
        T m0 = l + (r-l)/3;
        T m1 = r - (r-l)/3;
        T f0 = f(m0);
        T f1 = f(m1);

        if ((f0 < f1) ^ V) {
            l = m0;
        } else {
            r = m1;
        }
    }
    return {l, f(l)};
}

void solve() {
    int n; cin >> n;
    vector<double> x(n), y(n);
    vector<int> sx(n, 0), sy(n, 0);
    for (int i = 0; i < n; i++) {
        char d;
        cin >> x[i] >> y[i] >> d;
        if (d == 'L') sx[i] = -1;
        if (d == 'R') sx[i] = +1;
        if (d == 'D') sy[i] = -1;
        if (d == 'U') sy[i] = +1;
    }

    double _, res;
    tie(_, res) = ternary<double>(0.0, 1e9, [&](double t){
            double INF = 1e18;
            double mx = INF, my = INF, Mx = -INF, My = -INF;
            for (int i = 0; i < n; i++) {
                double nx = x[i] + t * sx[i];
                double ny = y[i] + t * sy[i];
                mx = min(mx, nx);
                Mx = max(Mx, nx);
                my = min(my, ny);
                My = max(My, ny);
            }
            return (Mx-mx)*(My-my);
            });
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
