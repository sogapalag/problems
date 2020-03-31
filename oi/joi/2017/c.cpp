#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

// the cut is monotonic,
// key, we know mi,mx. and focus index of mi
//          /
//         /
//   mi /
//    /
//   /  
// greedy take many as long as val in mi..r. while ensure other region in l..mx
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    int mi=1e9, mx=0;
    for (auto& a: g) {
        for (auto& x: a) {
            cin >> x;
            mi = min(mi, x);
            mx = max(mx, x);
        }
    }
    if (mx==mi) {
        cout << "0\n"; return;
    }
    vector<vector<int>> G[4];
    int idx[4], idy[4];
    for (int i = 0; i < 4; i++) {
        G[i] = g;
        if (i&1) {
            for (auto& a: G[i]) {
                reverse(a.begin(), a.end());
            }
        }
        if (i&2) {
            for (int x = 0; x < n/2; x++) {
                swap(G[i][x], G[i][n-1-x]);
            }
        }
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (G[i][x][y] == mi) {
                    idx[i] = x;
                    idy[i] = y;
                }
            }
        }
    }
    auto ck = [&](int lim){
        int r = mi + lim;
        int l = mx - lim;
        for (int _ = 0; _ < 4; _++) {
            auto& g = G[_];
            int rj = m;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < rj; j++) {
                    if (g[i][j] > r) {
                        rj = j;
                        break;
                    }
                }
                if (i == idx[_] && idy[_] >= rj) goto nxt;
                for (int j = rj; j < m; j++) {
                    if (g[i][j] < l) goto nxt;
                }
            }
            return true;
            nxt:;
        }
        return false;
    };
    int res = bs_first<int>(0, mx-mi, ck);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
