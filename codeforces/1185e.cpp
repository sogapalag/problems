#include <bits/stdc++.h>

using namespace std;

void maxi(int& x, int y){
    if(x<y)x=y;
}
void mini(int& x, int y){
    if(x>y)x=y;
}

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

// key: the mx must won't be cover by else.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) {
        cin >> x;
    }
    int mx = -1;
    vector<int> l(26, 1e8), r(26, -1), u(26, -1), d(26, 1e8);
    vector<bool> trk(26);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '.') {
                int x = s[i][j]-'a';
                maxi(mx, x);
                trk[x] = true;
                mini(l[x], j);
                maxi(r[x], j);
                maxi(u[x], i);
                mini(d[x], i);
            }
        }
    }
    vector<string> res(n, string(m, '.'));
    vector<tuple<int,int,int,int>> snakes;
    for (int x = 0; x <= mx; x++) {
        if (!trk[x]) {
            // for non exist, just use mx pos, since mx eventually cover it.
            int i = u[mx];
            int j = l[mx];
dbg(x,i,j);
            snakes.emplace_back(i,j,i,j);
        } else {
            int il = d[x], ir = u[x];
            int jl = l[x], jr = r[x];
dbg(x,il,jl,ir,jr);
            // must straight
            if (il!=ir && jl!=jr) {
                cout << "NO\n"; return;
            }
            snakes.emplace_back(il,jl,ir,jr);
            for (int i = il; i <= ir; i++) {
                for (int j = jl; j <= jr; j++) {
                    res[i][j] = char('a'+x);
                }
            }
        }
    }
dbg(res);
    // check same? since might invalid 'a' cover 'b'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (res[i][j] != s[i][j]) {
                cout << "NO\n"; return;
            }
        }
    }
    cout << "YES\n";
    cout << mx+1 << '\n';
    for (auto& _: snakes) {
        int il,jl,ir,jr;
        tie(il,jl,ir,jr) = _;
        il++;jl++;ir++;jr++;
        cout << il << ' ';
        cout << jl << ' ';
        cout << ir << ' ';
        cout << jr << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
