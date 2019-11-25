#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<pair<int, int>> a;
    for (int _ = 0; _ < k; _++) {
        int x,y;
        cin >> x >> y;
        if (x >= y) {
            a.emplace_back(x,y);
        }
    }
    sort(a.begin(), a.end());

    int res = n;
    int block = 0;
    for (auto& _: a) {
        int x,y;
        tie(x,y) = _;
        if (y+block < x) {
            res = x-1;
            break;
        } else if (y + block == x) {
            block++;
        }
    }

    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
