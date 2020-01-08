#include <bits/stdc++.h>

using namespace std;


// a direct pair contribution.
// one can simplify formula = 6(n-1) - 4 H_{n-1}
void solve() {
    int n; cin >> n;
    double suf = 0, s2 = 0;
    double res = 0;
    for (int i = n-1; i >= 0; i--) {
        double tmp = suf + (i>0);
        double ts2 = s2 + (i>0);
        res += tmp*tmp - ts2 + tmp;
        double prob = double(1)/i;
        if(i>0) suf += prob;
        if(i>0) s2 += prob*prob;
    }
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
