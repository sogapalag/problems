#include <bits/stdc++.h>

using namespace std;
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
using ll=long long;
//const ll INF = 0x3f3f3f3f'3f3f3f3f;
const int INF = 0x3f3f3f3f;
const int N = 111; 
const int K = 1024; 

int d[N][N];
int a[N][N];
int buy[N][K];
int sel[N][K];

ll w[N][N];
ll dis[N];

// prep i->j, profit (a), dist(d)
// we wanna bs \E sum(a)/sum(d) >= x 
//        <=>  \E sum (a-xd) >= 0
//        <=>  \E sum -(a-xd) <= 0.  (check negative cycle), but there's problem 0.99..998
//                         we have to manage to differ exactly =0, or 0.99 case.
//                         double is a workround method, but EPS still some error or TLE
//   or just run another floyd. check w[i][i]<=0
void solve() {
    memset(d, 0x3f, sizeof d);
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int x,y;
            cin >> x >> y;
            if (x==-1)x=1<<30;
            if (y==-1)y=0;
            buy[i][j] = x;
            sel[i][j] = y;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)if(j!=i) {
            for (int _ = 0; _ < k; _++) {
                a[i][j] = max(a[i][j], sel[j][_] - buy[i][_]);
            }
        }
    }
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        d[x][y] = z;
    }
    // floyd_warshall 
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {// for negative
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    // 0 disconnect ?
    auto ck = [&](ll x){
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)if(j!=i) {
                w[i][j] = d[i][j]==INF ? (1ll<<40) : -(a[i][j] - d[i][j]*x);
            }
        }
        memset(dis, 0x3f, sizeof dis);
        dis[0] = 0;
        // bellman-ford
        for (int _ = 0; _ < n; _++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)if(j!=i) {
                    if (dis[j] > dis[i]+w[i][j]) {
                        if (_==n-1) return true;
                        dis[j] = dis[i]+w[i][j];
                    }
                }
            }
        }
        return false;
    };
    auto ck2 = [&](ll x){
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                w[i][j] = (i==j||d[i][j]==INF)? INF*1ll*1000 : -(a[i][j]-d[i][j]*x);
            }
        }
        // floyd-warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    w[i][j] = min(w[i][j], w[i][k]+w[k][j]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (w[i][i] <= 0) return true;
        }
        return false;
    };
    //const double EPS = 1e-2;
    //double l = 0, r = 1e9+10;
    //while (r-l > EPS) {
    //    double x = (r+l)/2;
    //    if (ck(x)) l = x;
    //    else r = x;
    //}
    //cout << (int)floor(r);
    cout << bs_last<ll>(1, 1e9+1, ck2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
