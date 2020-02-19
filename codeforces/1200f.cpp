#include <bits/stdc++.h>

using namespace std;

const int N = 1024; 
const int P = 2520; 

int dp[N][P];
int8_t trk[N][P];
enum {
    FREE,
    VISITING,
    VISITED
};
int mod[N];
int g[N][10];

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
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        x %= P;
        if(x < 0) x += P; 
    }
    for (int i = 0; i < n; i++) {
        cin >> mod[i];
        for (int _ = 0; _ < mod[i]; _++) {
            cin >> g[i][_]; --g[i][_];
        }
    }
    auto advance = [&](int& x, int& y){
        x = g[x][y % mod[x]];
        (y += a[x]) %= P;
    };
    memset(trk, FREE, sizeof trk);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < P; j++) if(trk[i][j] == FREE){
            int x = i, y = j;
            vector<pair<int, int>> path;
            while (trk[x][y] == FREE) {
                path.emplace_back(x, y);
                trk[x][y] = VISITING;
                advance(x,y);
            }
            if(i == 0 && j == 5) {
                dbg(path, x, y);
            }
            if (trk[x][y] == VISITING) {
                set<int> s;
                while (!path.empty()) {
                    int u,v;
                    tie(u,v) = path.back(); path.pop_back();
                    trk[u][v] = VISITED;
                    s.insert(u);
                    if (u==x && v==y) break;
                }
                int res = s.size();
            if(i == 0 && j == 5) {
                dbg(res);
            }
                dp[x][y] = res;
                {// mark poped
                    int u=x,v=y;
                    while (true) {
                        advance(x,y);
                        dp[x][y] = res;
                        if (x == u && y == v) break;
                    }
                }
                for (auto& _: path) {
                    int u,v;
                    tie(u,v) = _;
                    dp[u][v] = res;
                    trk[u][v] = VISITED;
                }
            } else {
                for (auto& _: path) {
                    int u,v;
                    tie(u,v) = _;
                    dp[u][v] = dp[x][y];
                    trk[u][v] = VISITED;
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--; (y += a[x]) %= P;
        if (y < 0) y += P; // < 0 .. stupid, < P
        cout << dp[x][y] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
