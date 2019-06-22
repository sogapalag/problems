#include <bits/stdc++.h>

using namespace std;

// complete graph, (1,..,n-1) remove a edge from which, increase d2 exactly one
void solve() {
    int n, k;
    cin >> n >> k;
    int lim = (n-1) * (n-2) /2;
    if (k > lim) {
        cout << -1; return;
    }
    int m = n*(n-1)/2 - k;
    cout << m << "\n";
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j < n; j++) {
            if (cnt < k) {cnt++;}
            else {
                cout << i << ' ' << j << "\n";
            }
        }
    }
    for (int i = 1; i < n; i++) {
        cout << i << ' ' << n << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
