#include <bits/stdc++.h>

using namespace std;

#define LOCAL
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

using Bs = bitset<5050>;
Bs dp[5050];
// note 1/3 interchangable, and for each compo, 2-color, let(x,y) be size.
// then note exactly one of x/y should be color-B.
// so problem => find make it sum=#B
void solve() {
    int n,m;
    cin >> n >> m;
    int A,B,C;
    cin >> A >> B >> C;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> co(n,-1);
    function<void(int,int,int)> dfs = [&](int u, int p, int c){
        co[u] = c;
        for (int v: g[u])if(v!=p){
            if(co[v]==-1) dfs(v, u, c^1);
            else if (co[v] == c) {
                cout << "NO"; exit(0);
            }
        }
    };
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (co[i]==-1) {
            dfs(i,-1,c);
            c+=2;
        }
    }
    vector<int> cnt(c);
    for (int i = 0; i < n; i++) {
        cnt[co[i]]++;
    }
dbg(co, cnt);
    dp[0][0] = 1;
    for (int k = 0; k < c; k+=2) {
        int x = cnt[k];
        int y = cnt[k^1];
        dp[k/2 + 1] = (dp[k/2]<<x) | (dp[k/2]<<y);
    }
    if (!dp[c/2][B]) {
        cout << "NO"; return;
    }
    cout << "YES\n";
    vector<bool> inb(c);
    for (int k = c-2, now = B; k >= 0; k-=2) {
        int x = cnt[k];
        int y = cnt[k^1];
        if (now>=x && dp[k/2][now-x]) {
            inb[k] = true;
            now -= x;
        } else {
            inb[k^1] = true;
            now -= y;
        }
    }
    for (int i = 0; i < n; i++) {
        if (inb[co[i]]) co[i] = 2;
        else co[i] = 1;
    }
    for (int i = 0, cnt = 0; i < n; i++) {
        if (co[i]==1 && cnt<C) {
            co[i] = 3; ++cnt;
        }
    }
    for (auto& x: co) {
        cout << x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
