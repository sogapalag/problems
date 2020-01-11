#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,t;
    cin >> n >> m >> t;
    vector<int> X(m), Y(m);
    for (int i = 0; i < m; i++) {
        cin >> X[i] >> Y[i];
        X[i]--;Y[i]--;
    }
    if (t == 1) {
        const int N = 50008; 
        vector<bitset<N>> g(n);
        for (int i = 0; i < n; i++) {
            g[i][i] = 1;
        }
        for (int _ = m-1; _ >= 0; _--) {
            int x = X[_], y = Y[_];
            g[x] = (g[y] |= g[x]);
        }
        bitset<N> all_reach = g[0];
        for (int i = 1; i < n; i++) {
            all_reach &= g[i];
        }
        int w = all_reach._Find_first();
        if (w < n) {
            string s(m, '^');
            bitset<N> trk; trk[w] = 1;
            for (int i = m-1; i >= 0; i--) {
                int x = X[i], y = Y[i];
                if (trk[x] && !trk[y]) {
                    s[i] = '^';
                    trk[y] = 1;
                } else if (!trk[x] && trk[y]){
                    s[i] = 'v';
                    trk[x] = 1;
                }
            }
            cout << s;
        } else {
            cout << -1; return;
        }
    } else {
        if (n==2) {
            cout << -1; return;
        }
        vector<int> ids;
        for (int i = 0; i < m; i++) {
            if (Y[i] < 3) ids.push_back(i);
        }
        string s(m, '^');
        for (int _ = ids.size()-2; _ >= 0; _--) {
            int crt = ids[_], nxt = ids[_+1];
            int x = X[crt], y = Y[crt];
            int u = X[nxt], v = Y[nxt];
            // same dir
            if (x==u && y==v) s[crt] = s[nxt];
            // goto hole
            // thus cannot visit each edge.
            else {
                int k = 3 - u-v;
                if (x == k) s[crt] = '^';
                else assert(y==k), s[crt] = 'v';
            }
        }
        cout << s;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
