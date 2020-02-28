#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2020
#endif

void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 0; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    vector<int> cycle;
    vector<int> trk(n);
    vector<int> pa(n);
    function<void(int,int)> get_cycle = [&](int u, int p){
        pa[u] = p;
        trk[u] = 1;
        for (auto [v,_]: g[u])if(v!=p){
            if (!trk[v]) get_cycle(v,u);
            else if (trk[v] == 1) {
                int x = u;
                while (x != v) {
                    cycle.push_back(x);
                    x = pa[x];
                }cycle.push_back(x);
            }
        }
        trk[u] = 2;
    };
    get_cycle(0,-1);
    fill(trk.begin(), trk.end(), 0);
dbg(cycle);
    int m = cycle.size();
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        int v = cycle[i];
        int u = cycle[(i+1)%m];
        for (auto [_,w]:g[u])if(v==_)a[i]=w;
        trk[v] = 1;
    }
dbg(a);

    vector<ll> arm(n);
    ll ans = 0; // diameter may not use cycle, i.e. in some subtree
    function<ll(int,int,ll)> dfs = [&](int u, int p, ll depth){
        ll y = depth;
        trk[u] = 1;
        arm[u] = 0;
        for (auto [v,w]:g[u])if(v!=p&&!trk[v]){
            y = max(y, dfs(v,u,depth+w));
            ans = max(ans, arm[u] + arm[v] + w);
            arm[u] = max(arm[u], arm[v] + w);
        }
        return y;
    };
    // X0 --- X1 --- X2 ---
    // |      |      |
    // |      |      |
    // Y0     Y1     Y2
    vector<ll> X(m), Y(m);
    for (int i = 0; i < m; i++) {
        if(i)X[i] = X[i-1]+a[i-1];
        Y[i] = dfs(cycle[i], -1, 0);
    }
dbg(X,Y);
    // max pair of [0..i] / [i..m]
    vector<ll> pref(m), suff(m);
    ll mx = -(1ll<<60);
    for (int i = 0; i < m; i++) {
        pref[i] = mx + X[i]+Y[i];
        mx = max(mx, Y[i]-X[i]);
    }
    mx = -(1ll<<60);
    for (int i = m-1; i >= 0; i--) {
        suff[i] = mx + Y[i] - X[i];
        mx = max(mx, X[i] + Y[i]);
    }
    for (int i = 1; i < m; i++) {
        pref[i] = max(pref[i], pref[i-1]);
    }
    for (int i = m-1; i >= 1; i--) {
        suff[i-1] = max(suff[i-1], suff[i]);
    }
dbg(pref, suff);

    // for calc one at [0..i], anoter at (i..m], between-dist 
    vector<ll> L(m), R(m);
    for (int i = 0; i < m; i++) {
        L[i] = X[i]+Y[i];
        if(i) L[i] = max(L[i], L[i-1]);
    }
    for (int i = m-1; i >= 0; i--) {
        R[i] = (X[m-1]-X[i]+a[m-1]) + Y[i];
        if (i<m-1) R[i] = max(R[i], R[i+1]);
    }
dbg(L, R);

    ll res = pref[m-1];
    for (int i = 0; i < m-1; i++) {
        ll tmp = max(pref[i], suff[i+1]);
        tmp = max(tmp, L[i] + R[i+1]);
        res = min(res, tmp);
    }
    cout << max(ans, res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
