#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
using ll=long long;
const int N = 2525;

// key: use 4 points subset is enough
void solve() {
    int n; cin >> n;
    vector<vector<int>> ys(N);
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        ys[x].push_back(y);
    }
    for (auto& v: ys) {
        sort(v.begin(), v.end());
    }
    ll res = 0;
    for (int i = 0; i < N; i++) {
        if (ys[i].empty()) continue;
        Fenwick<int> fy(N);
        vector<bool> trk(N);
        for (int j = i; j < N; j++) {
            for (int y: ys[j])if(!trk[y]){
                trk[y] = 1;
                fy.add(y, 1);
            }
            // fix x l/r board as i/j
            if (j != i && !ys[j].empty()) {
                auto& yl = ys[i];
                auto& yr = ys[j];
                int il = 0, ir = 0;
                int low = 0;
                int L, R; // y bound, we should take from outside could extend the board.
                // iter y inc.
                while (il < yl.size() && ir < yr.size()) {
                    if (yl[il] < yr[ir]) {
                        L = yl[il++];
                        R = yr[ir];
                    } else if (yl[il] > yr[ir]) {
                        R = yl[il];
                        L = yr[ir++];
                    } else {
                        L = R = yl[il]; il++; ir++;
                        // up=R, must choose y<L=R
                        res += fy.query(low+1, L-1);
                        R++;
                    }
                    // constraint lower limit
                    res += fy.query(low+1, L) * 1ll * fy.query(R, N);
                    low = L;
                }
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
