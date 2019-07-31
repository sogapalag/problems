#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, I;
    cin >> n >> I;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int k = I*8/n;
    if (k >= 30) {
        cout << 0; return;
    }
    int K = 1<<k;
    if (K >= n) {
        cout << 0; return;
    }
    map<int, int> cnt;
    for (auto& x: a) {
        cnt[x]++;
    }
    vector<int> b;
    for (auto& p: cnt) {
        b.emplace_back(p.second);
    }
    if (b.size() <= K) {
        cout << 0; return;
    }
    int mx = 0;
    for (int i = 0; i < K; i++) {
        mx += b[i];
    }
    int tmp = mx;
    for (int i = K; i < (int)b.size(); i++) {
        tmp += b[i] - b[i-K];
        mx = max(mx, tmp);
    }
    cout << (n-mx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
