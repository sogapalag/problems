#include <bits/stdc++.h>

using namespace std;

// let boarder x,y of AB, BC
// simlify cost func to f(x) + g(y), x<=y
//
// some method with LIS work?
void solve() {
    int A,B,C;
    cin >> A >> B >> C;
    int n = A+B+C;
    vector<int> a(n+1), c(n+2);
    for (int _ = 0; _ < A; _++) {
        int x; cin >> x;
        a[x] = 1;
    }
    for (int _ = 0; _ < B; _++) {
        int x; cin >> x;
    }
    for (int _ = 0; _ < C; _++) {
        int x; cin >> x;
        c[x] = 1;
    }
    for (int i = 0; i < n; i++) {
        a[i+1] += a[i];
    }
    for (int i = n-1; i >= 0; i--) {
        c[i] += c[i+1];
    }
    vector<int> f(n+1), g(n+1);
    for (int i = 0; i <= n; i++) {
        //     leave       fill       dup from c
        f[i] = (A-a[i]) + (i-a[i]) - (C-c[i+1]);
        g[i] = (C-c[i+1]) + (n-i -c[i+1]) - (A - a[i]);
    }
    int res = 1<<30;
    int mi = 1<<30;
    for (int i = 0; i <= n; i++) {
        mi = min(mi, f[i]);
        res = min(res, mi + g[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
