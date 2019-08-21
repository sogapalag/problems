#include <bits/stdc++.h>

using namespace std;

struct Op {
    int x,y,u,v;
    Op() {}
    Op(int _x,int _y,int _u,int _v):x(_x), y(_y),u(_u),v(_v){} 
};

int a[512][512];

// --->|
// <---
// |--->
// keep move the odd
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<Op> res;
    for (int i = 1; i <= n; i++) {
        if (i&1) {
            for (int j = 1; j < m; j++) {
                if (a[i][j] & 1) {
                    res.emplace_back(i,j,i,j+1);
                    a[i][j]--;
                    a[i][j+1]++;
                }
            }
            if (i != n && (a[i][m] & 1)) {
                res.emplace_back(i,m,i+1,m);
                a[i][m]--;
                a[i+1][m]++;
            }
        } else {
            for (int j = m; j >= 2; j--) {
                if (a[i][j] & 1) {
                    res.emplace_back(i,j,i,j-1);
                    a[i][j]--;
                    a[i][j-1]++;
                }
            }
            if (i != n && (a[i][1] & 1)) {
                res.emplace_back(i,1,i+1,1);
                a[i][1]--;
                a[i+1][1]++;
            }
        }
    }
    cout << res.size() << "\n";
    for (auto& p: res) {
        cout << p.x << ' ' << p.y << ' '<< p.u <<' '<<p.v<<"\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
