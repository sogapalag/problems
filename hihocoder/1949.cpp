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

#define dbg(x) cout<<#x<<" = "<<(x)<<endl;
#define ones(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
#define ctz(x) __builtin_ctz(x)
#define lbit(x) ((x)&(-(x)))
#define hbit(x) 1<<(31-__builtin_clz(x))

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

#define __seg_p (int _l, int _r, int val, int p=1, int l=0, int r=N)
#define __seg_out if (_r <= l || r <= _l)
#define __seg_in if (_l <= l && r <= _r)
#define __seg_one if (l+1 == r)
#define __seg_calc int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
#define __seg_l (_l, _r, val, pl, l, m)
#define __seg_r (_l, _r, val, pr, m, r)

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100005;
const int CF = 300005;

const int N = 1005;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int n, m;
char mat[N][N];
//int d[N][N];
bool done[N][N];

void bfs(vpi & crt, int h=1){
    vpi nex;
    for (auto &p: crt){
        F0R(i, 4){
            int x = p.f + dx[i];
            int y = p.s + dy[i];
            if (mat[x][y] == '2'){
                cout << (h+1) << endl;
                exit(0);
            }
            if (!done[x][y]){
                nex.pb(mp(x,y));
                done[x][y] = true;
            }
        }
    }
    bfs(nex, h+1);
}

void solve() {
    cin >> n >> m;
    memset(mat, '#', sizeof mat);
    //memset(d, 0, sizeof d);
    memset(done, true, sizeof done);
    FOR(i, 1, n+1)
        cin >> (mat[i]+1);
    vpi crt;
    FOR(i, 1, n+1){
        FOR(j, 1, m+1){
            done[i][j] = false;
            if (mat[i][j] == '1')
                crt.pb(mp(i,j)), done[i][j]=true;
        }
    }
    bfs(crt);
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
