#include <bits/stdc++.h>

using namespace std;

// max weighted bipartite matching O(VE)~(n^2m)~(n^3)
// assignment problem, aka, hungary / kuhn / 
struct BipWeighted {
    //using T = int; static const T INF = 0x3f3f3f3f;
    using T = long long; static const T INF = 0x3f3f3f3f3f3f3f3f;
    int n, m; // #l, #r
    vector<int> left;
    vector<vector<T>> g;

    BipWeighted(int _n, int _m) : n(_n), m(_m)
        , left(m+1)
        , g(n, vector<T>(m))
    { assert(n <= m); } // make sure exist perfect matching
    BipWeighted(const vector<vector<T>>& _g) : n(_g.size()), m(_g[0].size())
        , left(m+1)
        , g(_g)
    { assert(n <= m); }

    T match() {
        fill(left.begin(), left.end(), -1);
        vector<T> L(n, -INF), R(m, 0); // label
        for (int l = 0; l < n; l++) {
            for (int r = 0; r < m; r++) {
                L[l] = max(L[l], g[l][r]);
            }
        }
        vector<T> slack(m);
        vector<int> pre(m, -1);
        vector<bool> trk(m+1);
        const int EMPTY = m; 

        for (int l = 0; l < n; l++) {
            fill(slack.begin(), slack.end(), INF);
            fill(trk.begin(), trk.end(), false);
            int x = l, y = EMPTY;
            left[y] = x;
            // while N(X) = Y, update label graph
            while (left[y] != -1) {
                trk[y] = true, x = left[y];
                T mi = INF; int id = -1;
                for (int r = 0; r < m; r++) {
                    if (!trk[r]) {
                        T tmp = L[x] + R[r] - g[x][r];
                        if (slack[r] > tmp) {
                            slack[r] = tmp; pre[r] = y;
                        }
                        if (mi > slack[r]) {
                            mi = slack[r]; id = r;
                        }
                    }
                }
                for (int r = 0; r < m; r++) {
                    if (trk[r]) {
                        L[left[r]] -= mi; R[r] += mi;
                    } else {
                        slack[r] -= mi;
                    }
                } L[l] -= mi;
                y = id;
            }
            // alternating augment
            do {
                left[y] = left[pre[y]];
                y = pre[y];
            } while(y != EMPTY);
        }

        T res = 0;
        for (int r = 0; r < m; r++) {
            if (left[r] != -1) {
                res += g[left[r]][r];
            }
        }
        return res;
    }
};
using ll=long long;
void solve() {
    int n; cin >> n;
    vector<vector<ll>> g(n, vector<ll>(n,0));
    for (int i = 0; i < n; i++) {
        int x,d,k;
        cin >> x >> d >> k;
        for (int j = 0; j < n; j++) {
            g[i][j] = x;
            if (j < k) x -= d;
            x = max(x, 0);
        }
    }

    BipWeighted bip(g);
    cout << bip.match();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
