#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
using ll=long long;//domino
// offline
// first note answer is #uncovered.
// which is diff of suff. (note not in direct view, but in scc/dsu view) since left seg may cover very far
void __solve() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        r[i] += l[i];
    }
    int q; cin >> q;
    vector<vector<pair<int,int>>> qrs(n);
    for (int i = 0; i < q; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        qrs[x].emplace_back(y,i);
    }

    vector<int> stk; // store scc(s)
    Dsu d(n);
    vector<ll> suff(n);
    
    vector<ll> res(q);
    for (int i = n-1; i >= 0; i--) {
        while (!stk.empty() && l[stk.back()] <= r[i]) {
            // merge
            r[i] = max(r[i], r[stk.back()]);
            d.join(i, stk.back()); // i pa
            stk.pop_back();
        }
        if (!stk.empty()) {
            suff[i] = suff[stk.back()] + l[stk.back()] - r[i];
        }
        stk.push_back(i);

        for (auto& _: qrs[i]) {
            int y,id;
            tie(y,id) = _;
            res[id] = suff[i] - suff[d.find(y)];
        }
    }
    for (auto& x: res) {
        cout << x << '\n';
    }
}

const int L = 19; 
const int N = 2e5+10; 
int pa[L][N];
ll sum[L][N];

// online binary lift
void solve() {
    int n; cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        r[i] += l[i];
    }
    vector<int> stk;
    pa[0][n] = n;
    for (int i = n-1; i >= 0; i--) {
        // pa[0] be first r[i] < r'
        // thus i won't be more profit, if does more, contribute by i'
        while (!stk.empty() && r[stk.back()] <= r[i]) {
            stk.pop_back();
        }
        if (stk.empty()) {
            pa[0][i] = n;
            sum[0][i] = 0;
        } else {
            pa[0][i] = stk.back();
            sum[0][i] = max(0, l[stk.back()] - r[i]);
        }
        stk.push_back(i);
    }
    for (int j = 1; j < L; j++) {
        for (int i = 0; i <= n; i++) {
            pa[j][i] = pa[j-1][ pa[j-1][i] ];
            sum[j][i] = sum[j-1][i] + sum[j-1][ pa[j-1][i] ];
        }
    }
    int q; cin >> q;
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        ll res = 0;
        for (int j = L-1; j >= 0; j--) {
            if (pa[j][x] <= y) {
                res += sum[j][x];
                x = pa[j][x];
            }
        }
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
