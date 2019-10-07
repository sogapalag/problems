#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, K;
    cin >> n >> K;
    vector<bool> dis(10, false);
    for (int _ = 0; _ < K; _++) {
        int x; cin >> x;
        dis[x] = true;
    }
    for (int i = n; ;i++) {
        bool has = false;
        int x = i;
        while (x) {
            has |= dis[x%10];
            x /= 10;
        }
        if (!has) {
            cout << i; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
