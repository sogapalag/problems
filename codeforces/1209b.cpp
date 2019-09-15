#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    auto f = [&](int i, int t)->bool{
        bool on = s[i]-'0';
        if (t < b[i]) return on;
        int pe = (t-b[i])/a[i];
        pe &= 1;
        return on^pe^1;
    };
    int res = 0;
    for (int t = 0; t < 300; t++) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (f(i,t)) cnt++;
        }
        res = max(res, cnt);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
