#include <bits/stdc++.h>

using namespace std;


void solve() {
    int m,bsz,n,tsz;
    cin >> m >> bsz >> n >> tsz;
    int M = 0;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
        M = max(M, x);
    }
    auto gg = [](){
        cout << -1;exit(0);
    };
    vector<int> t(M+1);
    for (int _ = 0; _ < tsz; _++) {
        int x; cin >> x;
        if (x > M) gg();
        t[x]++;
    }
    vector<int> b(M+1);
    int l = 0, r = 0;
    int fullfill = 0;
    while (l < m) {
        while (r < m && (r-l < bsz || fullfill < tsz)) {
            int x = a[r++];
            if (++b[x] <= t[x]) fullfill++;
        }
        if (fullfill == tsz && r-l >= bsz && min(l/bsz, n-1) + (m-r)/bsz >= n-1) {
            int cl = min(l/bsz, n-1);
            vector<int> res;
            for (int i = cl*bsz; i < l; i++) {
                res.push_back(i);
            }
            for (int i = l, del = 0; i < r && del+bsz < r-l; i++) {
                int x = a[i];
                if (b[x] > t[x]) {
                    b[x]--;
                    del++;
                    res.push_back(i);
                }
            }
            cout << res.size() << "\n";
            for (auto& x: res) {
                cout << x+1 << ' ';
            }return;
        }
        int x = a[l++];
        if (b[x]-- <= t[x]) fullfill--;
    }
    gg();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
