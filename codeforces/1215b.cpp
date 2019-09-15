#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<bool> neg(n, false);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x < 0) neg[i] = true;
    }

    int x[2]={0,0};
    long long sum = 0;
    bool odd = 0;
    for (int i = 0; i < n; i++) {
        x[odd]++;
        if (neg[i]) odd ^= 1;
        sum += x[odd^1];
    }

    long long res = 1ll*n*(n+1)/2 - sum;
    cout << sum << ' '<< res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
