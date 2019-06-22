#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int mi = 1e8, id = -1;
    auto f = [](int x){return -x-1;};
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x >= 0) x = f(x);
        if (x < mi) {mi=x; id=i;}
        a[i] = x;
    }
    if (n&1) {
        a[id] = f(a[id]);
    }
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
