#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n); // freq
    vector<int> c(n+1); // freq of a
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        a[x-1]++;
    }
    for (int x: a) c[x]++;

    int sum = n;
    int last = n;
    cout << last << "\n";
    int wasted = 0;
    // key idea, once we set best, those c>best must be wasted
    // keep track cumsum, wasted
    for (int i = 2; i <= n; i++) {
        while (last > sum/i) {
            int best = min(last, sum/i);
            for (int j = last; j > best; j--) {
                wasted += c[j];
                sum -= wasted;
            }
            last = best;
        }
        cout << last << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
