#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    if (k==1) {
        cout << "! 1"; return;
    }

    vector<pair<int, int>> a(k+3);
    for (int _ = 1; _ <= k+1; _++) {
        cout << "? ";
        for (int i = 1; i <= k+1; i++) {
            if (i!=_) {
                cout << i << ' ';
            }
        }cout << endl;
        int p, x;
        cin >> p >> x;
        a[_]={p,x};
    }

    int p, x;
    tie(p,x) = a[k+1];
    int y = a[p].second;
    int cnt = 0;
    // the easy way is just cnt occur time. don't think too much i<x?
    for (int i = 1; i <= k; i++) {
        if (i!=p) {
            if (x < y) {
                if (a[i].second==y) cnt++;
            } else {
                if (a[i].second==x) cnt++;
            }
        }
    }
    cout << "! "<< (cnt+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
