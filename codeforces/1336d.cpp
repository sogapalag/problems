#include <bits/stdc++.h>

using namespace std;


// it's obvious we should use delta info
// dt = c(x,2) => only trouble is x=0/1, dt=0
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> cond(n+1);
    int tri, row;
    cin >> tri >> row;
    int dt, dr;
    auto q = [&](int i){
        cout << "+ " << i << endl;
        int x,y;
        cin >> x >> y;
        dt = x-tri; tri = x;
        dr = y-row; row = y;
        for (int x = 1; ; x++) {
            if (x*(x-1)/2 == dt) {
                a[i] = x; break;
            }
        }
        cond[i] = dr;
    };
    // by cond(i) deduce a[i+1] = 0/1
    auto deduce = [&](int i){
        if (i > 2) cond[i] -= (a[i-2]+1) * (a[i-1]+1);
        if (a[i+1] >= 2) return;
        if (cond[i] == 0) a[i+1] = 0;
    };
    q(1);q(2);q(3);q(1); // 1 twice, ensure a[i]
    for (int i = 4; i < n; i++) {
        q(i);
    }
    deduce(2);
    if (a[2] == 1) {
        if ((a[2]+1) * (a[3]+1) != cond[1]) a[2] = 0;
    }
    assert((a[2]+1) * (a[3]+1) == cond[1]);
    --a[1];
    for (int i = 3; i < n; i++) {
        deduce(i);
    }
    a[n] = cond[n-1] / (a[n-2]+1);

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
