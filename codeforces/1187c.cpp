#include <bits/stdc++.h>

using namespace std;


// default set non-decreasing.
// modify those not must non-dec
// then must not non-dec iff it contains flag inc[]. since last step we modified.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        a[i] = i*2000;
    }
    vector<pair<int, int>> q;
    vector<bool> inc(n, false);
    for (int i = 0; i < m; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t) {
            for (int j = x; j < y; j++) {
                inc[j] = true;
            }
        } else {
            q.emplace_back(x, y);
        }
    }
    for (int i = 1; i < n; i++) {
        if (!inc[i]) {
            a[i+1] = a[i]-1;
        }
    }
    for (auto& p: q) {
        int x,y;
        tie(x,y) = p;
        bool T = false;
        for (int j = x; j < y; j++) {
            if (!inc[j]){
                T = true;
                break;
            }
        }
        if (!T) {
            cout << "NO"; return;
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
