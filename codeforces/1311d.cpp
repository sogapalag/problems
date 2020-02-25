#include <bits/stdc++.h>

using namespace std;

const int N = 20004; // B can up to 2e4
vector<int> ds[N];
void prep() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j+=i) {
            ds[j].push_back(i);
        }
    }
}
// one can brute-force all valid (a,b,c)
void solve() {
    int x,y,z;
    cin >> x >> y >> z;
    int res = 1e9;
    int u,v,w;
    // iter mid
    for (int b = 1; b < N; b++) {
        int tmp = abs(b-y);
        // closest c
        int c = z/b*b;
        if (!c) c+=b;
        if (abs(c+b - z) < abs(z-c)) c += b;
        tmp += abs(c-z);
        // closest a
        auto it = lower_bound(ds[b].begin(), ds[b].end(), x);
        if (it != ds[b].end()) {
            if (tmp + abs(x - *it) < res) {
                res = tmp + abs(x-*it);
                u=*it; v=b; w=c;
            }
        }
        if (it-ds[b].begin() > 0) {
            --it;
            if (tmp + abs(x - *it) < res) {
                res = tmp + abs(x-*it);
                u=*it; v=b; w=c;
            }
        }
    }
    cout << res << "\n";
    cout << u << ' '<<v<<' '<<w << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
