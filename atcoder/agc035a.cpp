#include <bits/stdc++.h>

using namespace std;


// a0=a3
void solve() {
    int n; cin >> n;
    map<int, int> cnt;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
    }
    if (cnt.size() == 1) {
        if (cnt[0] == n) cout << "Yes";
        else cout << "No";
    } else if (cnt.size() == 2) {
        if (cnt[0]*3 == n && cnt.rbegin()->second * 3 == 2*n) {
            cout << "Yes";
        } else {
            cout << "No";
        }
    } else if (cnt.size() == 3) {
        int sum = 0;
        for (auto& p: cnt) {
            if (p.second * 3 != n) {
                cout << "No"; return;
            }
            sum ^= p.first;
        }
        if (sum == 0) cout << "Yes";
        else cout << "No";
    } else {
        cout << "No";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
