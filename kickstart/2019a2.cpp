#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

int R, C;
char m[256][256];
int d[256][256];

void bfs(vpi& layer, int depth){
    if (sz(layer) == 0) return;
    vpi nex;
    nex.reserve(1000);
    for (auto p: layer){
        if (d[p.f+1][p.s] == 0 && m[p.f+1][p.s] == '0'){
            d[p.f+1][p.s] = depth;
            nex.pb(mp(p.f+1, p.s));
        }
        if (d[p.f-1][p.s] == 0 && m[p.f-1][p.s] == '0'){
            d[p.f-1][p.s] = depth;
            nex.pb(mp(p.f-1, p.s));
        }
        if (d[p.f][p.s+1] == 0 && m[p.f][p.s+1] == '0'){
            d[p.f][p.s+1] = depth;
            nex.pb(mp(p.f, p.s+1));
        }
        if (d[p.f][p.s-1] == 0 && m[p.f][p.s-1] == '0'){
            d[p.f][p.s-1] = depth;
            nex.pb(mp(p.f, p.s-1));
        }
    }
    bfs(nex, depth+1);
}

bool work(int k){
    int xm = 11111, ym = 11111;
    int xM = -11111, yM = -11111;
    FOR(i, 1, R+1){
        FOR(j, 1, C+1){
            if (d[i][j] > k){
                xm = min(xm, i-j);
                xM = max(xM, i-j);
                ym = min(ym, i+j);
                yM = max(yM, i+j);
            }
        }
    }
    if (xm == 11111){
        // implies no > k
        return true;
    }
    FOR(i, 1, R+1){
        FOR(j, 1, C+1){
            int xym = max(abs(i-j-xm), abs(i+j-ym));
            int xyM = max(abs(i-j-xM), abs(i+j-yM));
            int manh = max(xym, xyM);
            if (manh <= k){
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int res = 500;
    memset(m, 0, sizeof m);
    memset(d, 0, sizeof d);
    cin >> R >> C;
    FOR(i, 1, R+1) cin >> (m[i]+1);
    //cout << m[1][1] << m[1][2];
    vpi layer;
    layer.reserve(1000);
    FOR(i, 1, R+1){
        FOR(j, 1, C+1){
            if (m[i][j] == '1') {
                layer.pb(mp(i,j));
            }
        }
    }
    bfs(layer, 1);
 //   FOR(i, 1, R+1){
 //       FOR(j, 1, C+1){
 //           cout << d[i][j];
 //       }
 //       cout << endl;
 //   }
    int l = 0, r = 500; //[)
    while (l != r){
        int mid = (l+r)/2;
        if (work(mid)){
            res = min(res, mid);
            r = mid;
        }else{
            l = mid+1;
        }
    }
    cout << res;
}

int main() {
    int T; cin >> T;
    FOR(i,1,T+1) {
        cout << "Case #" << i << ": ";
        solve();
        cout << endl;
    }
}
