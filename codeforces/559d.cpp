#include <bits/stdc++.h>

using namespace std;


// https://cp-algorithms.com/geometry/area-of-simple-polygon.html
// https://cp-algorithms.com/geometry/picks-theorem.html
// consider contribution a (directed)side of polygon
// by area formula, calcel sum xx'-yy' = 0, so when a side join, its contribution = xy'-x'y
// and point on this segment, used gcd compute.
// magic is that we don't count many segs, we only consider i->j with j-i < LARGE = 60
// since its occurrent prob = #polygon use (i,j) / #all polygon = below. while k>>60, this prob ~ 2^{k+1}->0
void solve() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    double tot = pow<double>(2.0, n) - 1 - n - n*(n-1)/2; // #all polygon
    const int LARGE = 60; 
    vector<double> pw(LARGE+1);
    pw[0] = 1;
    for (int i = 1; i <= LARGE; i++) {
        pw[i] = pw[i-1]/2.0;
    }
    double res = 0;
    for (int i = 0; i < n; i++) {
        for (int k = 1; k < n && k < LARGE; k++) {
            int j = (i+k)%n;
            double prob = n > LARGE ? pw[k+1] : (1/pw[n-k-1] - 1)/tot;
            double area = 1ll*x[i]*y[j] - 1ll*x[j]*y[i];
            double bpnt = __gcd(abs(x[i]-x[j]), abs(y[i]-y[j]));
            res += (area - bpnt) * prob;
        }
    }
    res = res/2 + 1;
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
