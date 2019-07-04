#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> sum(n+1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        sum[i] = sum[i-1] + x;
    }
    map<int, vector<pair<int, int>>> a;
    for (int r = 1; r <= n; r++) {
        for (int l = 1; l <= r; l++) {
            int x = sum[r] - sum[l-1];
            a[x].emplace_back(l, r);
        }
    }
    int k = 0;
    vector<pair<int, int>> res;
    for (auto& v: a) {
        int cnt = 0; int las = -1;
        vector<pair<int, int>> tmp;
        for (auto& p: v.second) {
            if (p.first > las) {
                cnt++; las = p.second;
                tmp.push_back(p);
            }
        }
        if (cnt > k) {
            k = cnt;
            res = tmp;
        }
    }
    cout << k << "\n";
    for (auto& p: res) {
        cout << p.first << ' ' << p.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
