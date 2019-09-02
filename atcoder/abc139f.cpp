#include <bits/stdc++.h>

using namespace std;
using cd=complex<double>;

void solve() {
    int n; cin >> n;
    vector<cd> a(n);
    for (auto& p: a) {
        double x,y;
        cin >> x >> y;
        p = {x,y};
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return arg(u) < arg(v);
    });
    double res = 0;
    for (int i = 0; i < n; i++) {
        cd crt;
        for (int j = 0; j < n; j++) {
            crt += a[(i+j)%n];
            res = max(res, abs(crt));
        }
    }
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
