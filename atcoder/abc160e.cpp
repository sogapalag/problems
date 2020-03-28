#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,A,B,C;
    cin >> n >> m >> A >> B >> C;
    vector<int> a(A),b(B),c(C);
    for (auto& x: a) cin >> x;
    for (auto& x: b) cin >> x;
    for (auto& x: c) cin >> x;
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());
    a.resize(n);
    b.resize(m);
    for (int x:a)c.push_back(x);
    for (int x:b)c.push_back(x);
    sort(c.begin(), c.end(), greater<int>());
    long long res = 0;
    for (int i = 0; i < n+m; i++) {
        res += c[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
