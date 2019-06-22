#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, q;
    cin >> n >> q;
    deque<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> res(n+1);
    res[1] = {a[0], a[1]};
    for (int i = 2; i <= n; i++) {
        int A = a[0], B = a[1];
        a.pop_front();
        a.pop_front();
        if (A > B) {
            a.push_front(A);
            a.push_back(B);
        } else {
            a.push_front(B);
            a.push_back(A);
        }
        res[i] = {a[0], a[1]};
    }
    while (q--) {
        long long x;
        cin >> x;
        if (x <= n) {
            cout << res[x].first << ' ' << res[x].second << "\n";
        } else {
            x = (x-n) % (n-1);
            cout << a[0] << ' ' << a[x+1] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
