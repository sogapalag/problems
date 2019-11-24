#include <bits/stdc++.h>

using namespace std;


// greedy backwards
void solve() {
    int n,m;
    cin >> n >> m;
    string s;cin >> s;
    vector<int> a;
    for (int i = 0; i <= n; i++) {
        if (s[i]=='0') a.push_back(i);
    }

    vector<int> res;
    int x = n;
    while (x != 0) {
        int y = *lower_bound(a.begin(), a.end(), x-m);
        if (y == x) {
            cout << -1; return;
        }
        res.push_back(x-y);
        x = y;
    }
    reverse(res.begin(), res.end());
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
