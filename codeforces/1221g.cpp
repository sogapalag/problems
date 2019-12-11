#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 40; 
int n,m;
vector<int> g[N];
ll adj[N];

int count_isolated() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].empty()) cnt++;
    }
    return cnt;
}
bool trk[N];
int co[N];
void dfs(int u, int c) {
    trk[u] = true;
    co[u] = c;
    for (int v: g[u]) {
        if (!trk[v]) dfs(v,c^1);
    }
}
int count_components() {
    static int res = -1;
    if (res != -1) return res;
    memset(trk, 0, sizeof trk);
    res = 0;
    for (int i = 0; i < n; i++) {
        if (!trk[i]) {
            dfs(i, 0);
            res++;
        }
    }
    return res;
}
bool is_2color() {
    memset(trk, 0, sizeof trk);
    for (int i = 0; i < n; i++) {
        if (!trk[i]) dfs(i, 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j: g[i]) {
            if (co[i] == co[j]) return false;
        }
    }
    return true;
}

ll sum[1<<20];
ll count_indep_sets() {
    int a = (n+1)/2; // [0..a)
    int b = n - a;   // [a..n)
    const int MA = 1<<a; 
    const int MB = 1<<b; 
    memset(sum, 0, sizeof sum);
    // sum[mb] := #IS(ma), s.t. N_b(ma) = mb
    for (int ma = 0; ma < MA; ma++) {
        ll nei = 0;
        for (int i = 0; i < a; i++) {
            if (ma>>i&1) {
                if (nei>>i&1) goto not_IS;
                nei |= (1<<i) | adj[i];
            }
        }
        sum[nei>>a]++;
        not_IS:;
    }

    // SoS, now, := #IS(ma), s.t. N_b(ma) subsets mb
    for (int i = 0; i < b; i++) {
        for (int mb = 0; mb < MB; mb++) {
            if (mb>>i&1) sum[mb] += sum[mb^(1<<i)];
        }
    }

    ll res = 0;
    // for each IS(mb), use nei(i.e. ma) s.t. N_b(ma) subsets complement(mb)
    // i.e. can merge to IS
    for (int mb = 0; mb < MB; mb++) {
        ll nei = 0;
        for (int i = 0; i < b; i++) {
            if (mb>>i&1) {
                if (nei>>(i+a)&1) goto not_IS_;
                nei |= (1ll<<(i+a)) | adj[i+a];
            }
        }
        res += sum[mb^(MB-1)];
        not_IS_:;
    }
    return res;
}

ll calc(int msk) {
    // {}, all isolated?
    if (msk == 0b000) return m == 0? (1ll<<n) : 0;
    // {0}, {2}, only isolated are free
    if (msk == 0b001 || msk == 0b100) return 1ll << count_isolated();
    // {1}, each compo should 2-coloring
    if (msk == 0b010) return (is_2color() ? (1ll<<count_components()) : 0);
    // {0,1} {1,2}, IS color 1. thus no 1+1=2
    if (msk == 0b011 || msk == 0b110) return count_indep_sets();
    // {0,2}, each compo use one color
    if (msk == 0b101) return 1ll << count_components();
    // {0,1,2}, all
    if (msk == 0b111) return 1ll << n;
}

void solve() {
    cin >> n >> m;
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
        adj[x] |= 1ll << y;
        adj[y] |= 1ll << x;
    }
    // IEP, e subsets msk
    ll res = 0;
    for (int i = 0; i < 8; i++) {
        //cout << calc(i) << "\n";
        res += (__builtin_popcount(i)&1) ? +calc(i): -calc(i);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
