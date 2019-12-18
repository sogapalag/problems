#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

// note for >1, should star shape
// for odd 2k+1, could many k+1, and at most one k
// for even 2k,  could many k, and at most k+1; since k+1>k, so just find many k.
// there still a case for even. shape like 
//!     \   /  !
//!      u-p   !
//!     /   \  !
//
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> deg(n, 0);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;
        deg[y]++;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    vector<int> res(n+1);
    fill(res.begin(), res.end(), 1);
    res[1] = *max_element(deg.begin(), deg.end()) + 1;
    
    vector<int> mx(n), pa(n,-1);
    vector<vector<int>> subs(n); // max depth of each sub
    function<void(int,int)> dfs = [&](int u,int p){
        for (int v: g[u])if(v!=p){
            pa[v]=u;
            dfs(v,u);
            subs[u].push_back(mx[v]+1);
            mx[u] = max(mx[u], mx[v]+1);
        }
    };
    dfs(0,-1);

    vector<int> up(n);
    function<void(int,int)> get_up = [&](int u,int p){
        sort(subs[u].begin(), subs[u].end());
        int m = subs[u].size();
        for (int v: g[u])if(v!=p){
            int best_down = (mx[v]+1==subs[u][m-1]? (m>1?subs[u][m-2]:0) : subs[u][m-1]);
            up[v] = max(best_down, up[u]) + 1;
            get_up(v,u);
        }
    };
    get_up(0,-1);

    auto update = [&](int u){
        auto& a = subs[u];
        int m = a.size();
        for (int i = 0; i < m; i++) { // -1, otherwise, x*2>n overflow
            int x = a[i];
            if(i+1<m) res[x*2] = max(res[x*2], m-i);
            if (x>1) {
                if(i+1<m)res[x*2-1] = max(res[x*2-1], m-i);
                if (i>0) {
                    int y = min(a[i-1], x-1);
                    res[y*2+1] = max(res[y*2+1], m-i+1);
                }
            }
        }
        int p = pa[u];
        if (p==-1||deg[u]<3||deg[p]<3) return;
        int idp = -1;
        for (int i = 0; i < m; i++) {
            if (a[i] == up[u]) {idp=i;break;}
        }
        int snd_best = idp<m-2 ? a[m-2] : a[m-3];
        //for (int k = snd_best; k >= 1; k--) {
        //    int i = lower_bound(a.begin(), a.end(), k) - a.begin();
        //    int sum = m-i - (i<=idp);
        //    //if (sum <= 1) break;
        //    int j = lower_bound(subs[p].begin(), subs[p].end(), k) - subs[p].begin();
        //    int oth = deg[p]-j - 1;
        //    //if (oth <= 1) break;
        //    res[k*2] = max(res[k*2], sum+oth);
        //}
        // above both work, while below could early stop, since sum/oth <= 1, is included in base case
        for (int k = 1; k <= snd_best; k++) {
            int i = lower_bound(a.begin(), a.end(), k) - a.begin();
            int sum = m-i - (i<=idp);
            if (sum <= 1) break;
            int j = lower_bound(subs[p].begin(), subs[p].end(), k) - subs[p].begin();
            int oth = deg[p]-j - 1;
            if (oth <= 1) break;
            res[k*2] = max(res[k*2], sum+oth);
        }
    };
    for (int i = 0; i < n; i++) {
        if(up[i]) subs[i].push_back(up[i]);
        assert((int)subs[i].size() == deg[i]);
        sort(subs[i].begin(), subs[i].end());
    }
dbg(subs);
    for (int i = 0; i < n; i++) {
        update(i);
    }
    for (int i = n-2; i >= 1; i--) {
        res[i] = max(res[i], res[i+2]);
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
