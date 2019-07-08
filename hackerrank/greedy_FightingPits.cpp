#include <bits/stdc++.h>

using namespace std;

using ll=long long;

// sum x>= sum y, => x win
// TODO need rigorous proof
void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<vector<int>> t(k+1);
    vector<vector<ll>> sum(k+1);
    for (int _ = 0; _ < n; _++) {
        int s, i;
        cin >> s >> i;
        t[i].emplace_back(s);
    }
    for (int i = 1; i <= k; i++) {
        sort(t[i].begin(), t[i].end());
        int sz = t[i].size();
        sum[i].resize(sz);
        ll tmp = 0;
        for (int j = 0; j < sz; j++) {
            sum[i][j] = (tmp += t[i][j]);
        }
    }
    auto win = [&](int x, int y){
        int a = t[x].size(), b = t[y].size();
        if (a==0) return y;
        while (true) {
            if (t[x][a-1] >= b) return x;
            if (sum[x][a-1] >= sum[y][b-1]) return x;
            b -= t[x][a-1];
            swap(a,b); swap(x,y);
        }
    };
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            t[y].emplace_back(x);
            sum[y].emplace_back(x + (sum[y].empty()?0:sum[y].back()));
        } else {
            cout << win(x, y) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
