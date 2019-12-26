#include <bits/stdc++.h>

using namespace std;

const int N = 333; 
bool g[N][N];
int a[N];
bool trk[N];

int n,m;
vector<int> cons;
void dfs(int u) {
    cons.push_back(u);
    trk[u] = true;
    for (int i = 0; i < n; i++) {
        if (!trk[i] && g[u][i]) {
            dfs(i);
        }
    }
}

// Certificate
struct Certi {
    int x;
    vector<int> a;
    Certi() {x=0;}
    Certi(int _x) : x(_x) {}
    Certi& operator+=(const Certi& c){
        x += c.x;
        for(int i: c.a) a.push_back(i);
        return *this;
    }
};

Certi calc(vector<int> V, bool clique) {
    if (V.size()==1) {
        Certi res;
        res.x = a[V[0]];
        res.a = V;
        return res;
    }
    // clear history
    for (int i: V) trk[i] = false;
    // take complement
    for (int i: V) {
        for (int j: V) {
            g[i][j]^=1;
        }
    }
   
    Certi sum;
    for (int i: V) {
        if (trk[i]) continue;
        cons.clear();
        dfs(i);
        // sub problem
        auto tmp = calc(cons, clique^1);
        if(clique) sum += tmp;
        else if (tmp.x > sum.x) {
            sum = tmp;
        }
    }
    return sum;
}

// based on this problem description, an scc's complement must |scc|>1.
//  so can keep take complement, the problem is MIS or Mclique. sum or max.
// in general graph, NP-hard for sure.
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x][y]=g[y][x]=1;
    }
    Certi res;
    for (int i = 0; i < n; i++) {
        if (trk[i]) continue;
        cons.clear();
        dfs(i);
        auto tmp = calc(cons, true);
        if (tmp.x > res.x) {
            res = tmp;
        }
    }
    cout << res.x << "\n";
    cout << res.a.size() << "\n";
    for (int i: res.a) {
        cout << i+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
