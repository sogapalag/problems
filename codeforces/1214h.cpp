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

// for each u of diamter, depth=ck(u).
// let x,y be #points to diamter ends. then if depth>0 && depth+x >=k, depth+y>=k. ans=NO.
// since we can only color the foot keep -1, or +1.
void solve() {
    int n,k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    // two-color
    if (k == 2) {
        cout << "Yes" << "\n";
        vector<int> co(n);
        function<void(int,int)> two = [&](int u,int p){
            for (int v: g[u])if(v!=p) {
                co[v] = co[u] ^ 1;
                two(v, u);
            }
        };
        two(0,-1);
        for (auto& x: co) {
            cout << (x+1) << ' ';
        }
        return;
    }
    // find diamter
    vector<int> d(n);
    vector<int> pa(n);
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p) {
            d[v] = 1 + d[u];
            pa[v] = u;
            dfs(v, u);
        }
    };
    d[0]=1; pa[0]=-1; dfs(0,-1);
    int root = max_element(d.begin(), d.end()) - d.begin();
    d[root]=1; pa[root]=-1; dfs(root,-1);
    int tail = max_element(d.begin(), d.end()) - d.begin();
    if (d[tail] < k) {
        cout << "Yes" << "\n";
        for (int _ = 0; _ < n; _++) {
            cout << "1 ";
        }
        return;
    }
    vector<bool> trk(n, false);
    vector<int> co(n);
    vector<int> pth;
    {
        int cnt = 0;
        int x = tail;
        trk[x] = true; pth.emplace_back(x); 
        co[x] = cnt; (cnt+=1)%=k;
        while (pa[x] != -1) {
            x = pa[x];
            trk[x] = true;
            pth.emplace_back(x);
            co[x] = cnt; (cnt+=1)%=k;
        }
    }
    // get foot depth
    function<int(int)> ck = [&](int u){
        int depth = 0;
        for (int v: g[u])if(!trk[v]){
            trk[v]=true;
            depth = max(depth, 1+ck(v));
        }
        return depth;
    };
    int D = d[tail];
    int m = pth.size();
    vector<int> dir(m);
    // check foot depth is small enough
    for (int i = 0; i < m; i++) {
        int x = i+1, y = D-i, u = pth[i];
        int depth = ck(u);
        dbg(depth,x,y,u);
        if (depth && depth + x >= k && depth + y >= k) {
            cout << "No"; return;
        }
        if (depth + x < k) dir[i] = -1;
        if (depth + y < k) dir[i] = +1;
    }
    // color foot in -1/+1
    function<void(int,int)> foot = [&](int u,int o){
        for (int v: g[u])if(!trk[v]){
            trk[v] = true;
            co[v] = (co[u] + o + k) % k;
            foot(v,o);
        }
    };
    fill(trk.begin(), trk.end(), false);
    for (int u: pth) trk[u]=true;
    for (int i = 0; i < m; i++) {
        int u = pth[i], o = dir[i];
        foot(u, o);
    }
    cout << "Yes" << "\n";
    for (int i = 0; i < n; i++) {
        cout << (co[i]+1) << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
