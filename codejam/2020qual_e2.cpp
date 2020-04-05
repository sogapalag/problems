#include <bits/stdc++.h>

using namespace std;

struct Bip {
    int n,m; // #l, #r
    vector<vector<int>> g;
    vector<int> left;
    vector<bool> trk;

    Bip(int _n) : n(_n), m(_n) {
        init();
    }
    Bip(int _n, int _m) : n(_n), m(_m) {
        init();
    }
    void init() {
        g.resize(n);
        left.assign(m, -1);
        trk.assign(n, false);
    }
    inline void add(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 <= r && r < m);
        g[l].emplace_back(r);
    }

    bool dfs(int l) {
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    }
    int match() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        return cnt;
    }
};

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

const int N = 105; 
int a[N][N];
bool trk[N][N];

// claim: any diag is valid except form n-1 x, 1 y, x!=y. TODO proof
// hall.

//void solve(int n, int k) {
void solve() {
    int n,k;
    cin >> n >> k;
    //cout << n <<' '<< k <<endl;
    if (k == n+1 || k == n*n-1) {
        cout << "IMPOSSIBLE\n"; return;
    }
    if (n == 3 && (k == 5 || k == 7)) {
        cout << "IMPOSSIBLE\n"; return;
    }
    cout << "POSSIBLE\n";
    if (n == 2) {
        if (k == 2) cout << "1 2\n2 1\n";
        if (k == 4) cout << "2 1\n1 2\n";
        return;
    }
    // WA, don't know why
    auto ckfail = [&](int x, int y, int z){
        --x,--y,--z;
        memset(a, 0, sizeof a);
        memset(trk, 0, sizeof trk);
        for (int i = 0; i < n; i++) {
            int k = i<n-2 ? x : (i<n-1? y : z);
            a[i][i] = k;
            trk[k][i] = true;
        }
        for (int i = 0; i < n; i++) {
            Bip g(n);
            for (int j = 0; j < n; j++)if(j!=i) {
                for (int k = 0; k < n; k++) {
                    if (!trk[k][j]) g.add(k, j);
                }
            }
            int k = i<n-2 ? x : (i<n-1? y : z);
            g.add(k, i);
            //assert(g.match() == n);
            int cnt = g.match();
dbg(cnt, g.left); assert(cnt==n);
            for (int j = 0; j < n; j++) {
                a[i][j] = g.left[j];
                trk[a[i][j]][j] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j]+1 << ' ';
            }cout << '\n';
        }
    };
    auto ck = [&](int x, int y, int z){
        memset(a, 0, sizeof a); // clear
dbg(x,y,z);
        for (int i = 0; i < n-2; i++) {
            a[i][i] = x;
        }
        // fill occur first, AC
        vector<int> ord;
        ord.push_back(x);
        ord.push_back(y);
        ord.push_back(z);
        sort(ord.begin(), ord.end());
        ord.erase(unique(ord.begin(), ord.end()), ord.end());
        vector<bool> tmp(n+1);
        tmp[x]=tmp[y]=tmp[z]=true;
        for (int x = 1; x <= n; x++) {
            if (!tmp[x])ord.push_back(x);
        }
        a[n-2][n-2]=y; a[n-1][n-1] = z;
        //for (int x = 1; x <= n; x++) { // WA, still don't know why.
        for (int _ = 0; _ < n; _++) {
            int x = ord[_];
            int cnt = 0;
            vector<bool> fix(n), fjx(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (a[i][j] == x) {
                        cnt++;
                        fix[i] = fjx[j] = true;
                    }
                }
            }
            if (cnt == n) continue;
            Bip g(n);
            for (int i = 0; i < n; i++)if(!fix[i]) {
                for (int j = 0; j < n; j++)if(!fjx[j]) {
                    if (a[i][j] == 0) {
                        g.add(i, j);
                    }
                }
            }
dbg(x, g.g);
            cnt += g.match();
dbg(cnt, g.left);
            assert(cnt == n);
            for (int j = 0; j < n; j++) {
                int i = g.left[j];
                if (i != -1) a[i][j] = x;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << ' ';
            }cout << '\n';
        }
    };
    if (k%n == 0) ck(k/n,k/n,k/n);
    else {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++)if(y!=x) {
                for (int z = 1; z <= n; z++)if(z!=x) {
                    if (x*(n-2) + y + z == k) {
                        ck(x,y,z);return;
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //for (int n = 2; n <= 50; n++) {
    //    for (int k = n; k <= n*n; k++) {
    //        solve(n,k);
    //    }
    //}
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
