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

///    /\      .
///    \\\     . 
///    \ \     . 
///     \/
/// the problem key prat is decide between main-diag or counter-diag.
/// if one have faith, just impl try connect useful-link while you can.
///   the key proof why we won't miss one when there exist valid solution.
///   is that we make a cycle(topological) enclose/isolated other color. from outside
///      but this won't happen, since each time we try useful-link first, i.e. still different scc.
//        so there alway a hole to make the other color out.
//  since the whole process we don't make (unnecessary)cycle, so topologically, each color is valid scc.
//    if we do cycle like con A-A, enclosed B 
//       AB
//       BA  i.e. IMPOSSIBLE
//   so as long as there is valid, we can sure there won't be cycle. // one may need much more rigorous proof to seek help for topological..  or taiji..(kidding)..
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) {
        cin >> x;
    }
    vector<string> res(n-1, string(m-1, '.'));
    Dsu d(n*m);
    auto f = [&](int i,int j){
        return i*m+j; //m..
    };
    // | - V/H,con.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j+1<m && s[i][j] == s[i][j+1]) d.join(f(i,j), f(i,j+1));
            if (i+1<n && s[i][j] == s[i+1][j]) d.join(f(i,j), f(i+1,j));
        }
    }
    vector<vector<int>> scc(2);
    vector<int> cid(n*m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int k = s[i][j]-'A';
            int x = f(i,j);
            if (d.find(x) == x) {
                //cerr<<i<<' '<< j<<endl;
                cid[x] = scc[k].size();
                scc[k].push_back(x);
            }
        }
    }
    //cerr<<scc[0].size()<<' '<<scc[1].size()<<endl;
    Dsu cd[2]{scc[0].size(), scc[1].size()};
    //cerr<<cd[0].n<<' '<<cd[1].n<<endl;
    for (int i = 0; i+1 < n; i++) {
        for (int j = 0; j+1 < m; j++) {
            if (s[i][j]!=s[i+1][j+1])continue;
            if (s[i][j+1]!=s[i+1][j])continue;
            if (s[i][j]==s[i][j+1])continue;
            // AB  BA
            // BA  AB, other cases no need
            int c[2][2];
            for (int dx:{0,1}) {
                for (int dy:{0,1}){
                    c[dx][dy] = cid[d.find(f(i+dx,j+dy))];
                }
            }
            int k = s[i][j] - 'A';
            if (cd[k].join(c[0][0], c[1][1])) {
                res[i][j] = '\\';
            } else {
                res[i][j] = '/';
                cd[k^1].join(c[0][1], c[1][0]);
            }
        }
    }
    for (int k:{0,1}){
        set<int> rem;
        for (int i = 0; i < cd[k].n; i++) {
            rem.insert(cd[k].find(i));
        }
        if (rem.size() != 1) goto fail;
    }
    cout << "POSSIBLE\n";
    for (auto& x: res) {
        cout << x << '\n';
    }return;
fail:
    cout << "IMPOSSIBLE\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
