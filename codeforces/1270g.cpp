#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    // this step has thought, now find sum a = sum i, ai in [n]
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = i - x;
    }
    // but don't realize a semi-perm structure. maybe problem D cost too much time...

    for (int i = 1; i <= n; i++) {
        if (a[i] == i) {
            cout << "1\n" << i <<"\n"; return;
        }
    }
    vector<bool> trk(n+1, false);
    int u = 1; trk[u] = 1;
    vector<int> path; path.push_back(u);
    vector<int> res;
    while (true) {
        u = a[u];
        if (trk[u]) {
            while (path.back()!=u) {
                res.push_back(path.back());
                path.pop_back();
            }res.push_back(u);
            break;
        } else {
            trk[u] = 1;
            path.push_back(u);
        }
    }
    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
