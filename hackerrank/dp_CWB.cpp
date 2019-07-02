#include <bits/stdc++.h>

using namespace std;

using ll=long long;
unordered_map<ll, double> dp;

inline double ck(int m, int i) {
    return (m & (1<<i))? 1 : 0;
}
inline int clr(int m, int i) {
    return (m& ((1<<i)-1)) | ((m>>1) & ((-1)^((1<<i)-1)));
}

double f(int n, int k, int m) {
    if (k <= 0 || __builtin_popcount(m) == 0) return 0;
    if (dp.find( (((ll)k)<<32) | m ) != dp.end()) return dp[(((ll)k)<<32) | m];
    double sum = 0;
    for (int i = 0; i < n/2; i++) {
        sum += 2 * max(ck(m,i) + f(n-1, k-1, clr(m, i)),
                       ck(m,n-1-i) + f(n-1, k-1, clr(m, n-1-i)));
    }
    if (n&1) sum += ck(m, n/2) + f(n-1, k-1, clr(m, n/2));
    sum /= n;
    return dp[(((ll)k)<<32) | m] = sum;
}

// constant optimization, TLE on 22,23,24,25
// when case WBWBWBWBBBWBWBWWBW slower than WWWWWBBBBWWWWWW
// why irregular slow
// maybe take W while can might work; wrong.
void solve() {
    int n, k; cin >> n >> k;
    int m = 0;
    for (int i = 0; i < n; i++) {
        char x; cin >> x;
        if (x == 'W') m |= 1<<i;
    }
    cout << fixed << setprecision(8) << f(n,k,m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
