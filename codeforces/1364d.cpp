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
#define dbg(args...) 2020
#endif

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> depth(n), pa(n);
    vector<int> sta(n);
    int mx = -1, head, tail;
    function<void(int,int)> dfs = [&](int u, int p){
        sta[u] = 1;
        for (int v: g[u])if(v!=p && sta[v] <= 1){
            if (sta[v] == 1) {
                if (depth[v] > mx) {
                    mx = depth[v];
                    head = v, tail = u;
                }
                continue;
            }
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
        sta[u] = 2;
    };
    dfs(0,-1);
    if (m == n-1) {
        for (int c = 0; c < 2; c++) {
            vector<int> is;
            for (int i = 0; i < n; i++) {
                if ((depth[i]&1) == c) is.push_back(i);
            }
            if (is.size() >= (k+1)/2) {
                cout << "1\n";
                for (int i = 0; i < (k+1)/2; i++) {
                    cout << is[i]+1 << ' ';
                }
                return;
            }
        }
        assert(false);
    }
    vector<int> path;
    {
        int x = tail;
        while (x != head) {
            path.push_back(x);
            x = pa[x];
        }
        path.push_back(x);
    }
dbg(path);
    if (path.size() <= k) {
        cout << "2\n";
        cout << path.size() << "\n";
        for (auto& x: path) {
            cout << x+1 << ' ';
        }
    } else {
        cout << "1\n";
        for (int _ = 0, cnt = 0; _ < path.size(); _+=2) {
            if (cnt < (k+1)/2) {
                cout << path[_]+1 << ' ';
                ++cnt;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
