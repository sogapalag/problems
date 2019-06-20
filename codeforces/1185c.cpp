#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, M;
    cin >> n >> M;
    vector<int> cnt(101, 0);

    auto remain = [&](int lim){
        int r = 0;
        int have = 0;
        for (int i = 1; i <= 100; i++) {
            if (have + i*cnt[i] <= lim) {
                have += i*cnt[i];
                r += cnt[i];
            } else {
                r += (lim - have) / i; break;
            }
        }
        return r;
    };

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        cout << i-1 - remain(M-x) << ' ';
        cnt[x]++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
