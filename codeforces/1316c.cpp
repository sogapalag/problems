#include <bits/stdc++.h>

using namespace std;

// 1
// 0 0 0 0 x
// actually, find first i,j ai!=0, bj!=0. easy to impl.
void solve() {
    int n,m,p;
    cin >> n >> m >> p;
    vector<int> a(n), b(m);
    for (auto& x: a) {
        cin >> x;
        x %= p;
    }
    for (auto& x: b) {
        cin >> x;
        x %= p;
    }
    int mm = min(m,n);
    int i = 0;
    for (; i < mm; i++) {
        if (a[i] || b[i]) break;
    }
    assert(i < mm);
    if (a[i] && b[i]) {
        cout << i+i;
    } else if (a[i]){
        int k = i+1;
        for (; k < m; k++) {
            if (b[k]) break;
        }
        cout << i+k;
    } else {
        int k = i+1;
        for (; k < n; k++) {
            if (a[k]) break;
        }
        cout << i+k;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
