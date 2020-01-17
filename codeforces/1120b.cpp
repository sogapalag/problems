#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string a,b;
    cin >> a >> b;
    vector<int> d(n);
    long long tot = 0;
    for (int i = 0; i < n; i++) {
        d[i] = b[i] - a[i];
        if(i) d[i] -= d[i-1];
        tot += abs(d[i]);
    }
    if (d[n-1] != 0) {
        cout << -1; return;
    }
    cout << tot << "\n";
    tot = min(tot, 100000ll);
    // cannot alternating 0909... till the end, 
    // since this implies abs(d) inc. which is contradicted to d[n-1] = 0
    // although depth might be O(n), but O(n)operations is done too.
    function<void(int,int)> add = [&](int i, int x){
        if (x == 1 && a[i+1] == '9') add(i+1, -1);
        if (x ==-1 && a[i+1] == '0') add(i+1, +1);
        cout << (i+1) << ' ' << x << '\n';
        a[i] += x; a[i+1] += x;
        d[i] -= x;
        if (--tot == 0) exit(0);
    };
    for (int i = 0; i < n; i++) {
        while (d[i]) {
            add(i, d[i]>0?1:-1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
