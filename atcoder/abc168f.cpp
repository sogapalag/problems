#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

const int N = 4096; 
bool R[N][N], C[N][N], trk[N][N];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

// note total N^2 cell, so we can bfs them.
// impl-careful
void solve() {
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> vs, hs;
    vector<int> Xs, Ys;
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        Xs.push_back(x);
        Xs.push_back(y);
        Ys.push_back(z);
        vs.emplace_back(x,y,z);
    }
    for (int i = 0; i < m; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        Xs.push_back(x);
        Ys.push_back(y);
        Ys.push_back(z);
        hs.emplace_back(x,y,z);
    }
    Xs.push_back(0);
    Ys.push_back(0);
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    sort(Ys.begin(), Ys.end());
    Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());
dbg(Xs,Ys);
    int nx = Xs.size();
    int ny = Ys.size();
    if (Xs[0]==0 || Xs.back()==0 || Ys[0]==0 || Ys.back()==0) {
        cout << "INF"; return;
    }
    auto posx = [&](int x){
        return lower_bound(Xs.begin(), Xs.end(), x) - Xs.begin();
    };
    auto posy = [&](int y){
        return lower_bound(Ys.begin(), Ys.end(), y) - Ys.begin();
    };
    // R,C indicate blocked
    for (auto [x,y,z]:vs) {
        x=posx(x);
        y=posx(y);
        z=posy(z);
        for (int i = x; i < y; i++) {
            C[i][z] = true;
        }
    }
    for (auto [x,y,z]:hs) {
        x=posx(x);
        y=posy(y);
        z=posy(z);
        for (int j = y; j < z; j++) {
            R[x][j] = true;
        }
    }

    queue<pair<int,int>> q;
    {
        int x=posx(0);
        int y=posy(0);
        q.emplace(x,y); trk[x][y]=1;
        q.emplace(x-1,y); trk[x-1][y]=1;
        q.emplace(x,y-1); trk[x][y-1]=1;
        q.emplace(x-1,y-1); trk[x-1][y-1]=1;
    }
    while (!q.empty()) {
        auto [i,j] = q.front(); q.pop();
        if (i==0 && !R[i][j]) {
            cout << "INF"; return;
        }
        if (i==nx-2 && !R[i+1][j]) {
            cout << "INF"; return;
        }
        if (j==0 && !C[i][j]) {
            cout << "INF"; return;
        }
        if (j==ny-2 && !C[i][j+1]) {
            cout << "INF"; return;
        }
        for (int _ = 0; _ < 4; _++) {
            int x = i+dx[_];
            int y = j+dy[_];
            if (0<=x&&x<nx-1 && 0<=y&&y<ny-1 && !trk[x][y]) {
                if (x == i) {
                    if (!C[i][max(j,y)]) {
                        trk[x][y] = 1;
                        q.emplace(x,y);
                    }
                } else {
                    if (!R[max(i,x)][j]) {
                        trk[x][y] = 1;
                        q.emplace(x,y);
                    }
                }
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < nx-1; i++) {
        for (int j = 0; j < ny-1; j++) {
            if (trk[i][j]) {
                res += (Xs[i+1] - Xs[i]) *1ll* (Ys[j+1] - Ys[j]);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
