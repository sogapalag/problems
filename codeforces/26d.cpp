#include <bits/stdc++.h>

using namespace std;

double c(int n, int k) {
    double r = 1;
    while (k > 0) {
        r *= n--;
        r /= k--;
    }
    return r;
}
double cat(int n, int k, int m) {
    if (m > k) return c(n+k, n);
    if (m <= k-n) return 0;
    return c(n+k,n) - c(n+k,k-m);
}
// or one can use logfact to avoid float-error
double prob(int n, int k, int m) {
    if (m > k) return 1;
    if (m <= k-n) return 0;
    double res = 1;
    for (int i = 0; i < m; i++) {
        res *= (k-i);
        res /= (n+i+1);
    }
    return 1-res;
}
void solve() {
    int n,k,m;
    cin >> n >> k >> m;
    cout << fixed << setprecision(10) << prob(n,k,m+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
