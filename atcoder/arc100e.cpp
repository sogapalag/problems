#include <bits/stdc++.h>

using namespace std;

// i|j <= k  <=>  prefix of i|j sub k
// so for k, we upd by flip any setted bit. maintain two largest x
void solve() {
    int l; cin >> l;
    int n = 1<<l;
    vector<array<pair<int, int>, 2>> S(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        S[i][0] = {-1, -1};
        S[i][1] = {x, i};
    }

    int mx = 0;
    for (int i = 1; i < n; i++) {
        set<pair<int, int>> tmp;
        tmp.insert(S[i][0]);
        tmp.insert(S[i][1]);
        for (int j = l-1; j >= 0; j--) {
            if (i & (1<<j)) {
                tmp.insert(S[i^(1<<j)][0]);
                tmp.insert(S[i^(1<<j)][1]);
            }
        }
        S[i][1] = *tmp.rbegin();
        tmp.erase(S[i][1]);
        S[i][0] = *tmp.rbegin();
        int sum = S[i][0].first + S[i][1].first;
        mx = max(mx, sum);
        cout << mx << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
