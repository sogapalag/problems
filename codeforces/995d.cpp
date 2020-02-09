#include <bits/stdc++.h>

using namespace std;

// well this is trivial to me.
// although A/B wanna max/min, but since at each branch, A or B 1/2, obvious avg.
void solve() {
    int n,q;
    cin >> n >> q;
    const int MSK = 1<<n; 
    vector<int> f(MSK);
    double sum = 0;
    for (auto& x: f) {
        cin >> x;
        sum += x;
    }

    cout << fixed << setprecision(10);
    cout << sum/MSK << '\n';
    for (int _ = 0; _ < q; _++) {
        int i, x;
        cin >> i >> x;
        sum -= f[i];
        sum += f[i] = x;
        cout << sum/MSK << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
