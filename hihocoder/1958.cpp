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

const int N = 1e5+5;

int n; // nodes [1..n]
int m;

int tim; 
int low[MX];
int num[MX];
bool trk[MX];
vi stk;
//map<int, multiset<int>> graph;
vi graph[N];


//ll gloc, gcnt;

int lasv, size;

void tarjan(int v){
    low[v] = num[v] = tim++;
    stk.pb(v);
    trk[v] = true;
    for (auto u: graph[v]){
        if (!num[u])
            tarjan(u);
        if (trk[u])
            low[v] = min(low[v], low[u]);
    }
    // into scc
    if (low[v] == num[v]){
        // init scc sub_glob here
        int cnt = 0;
        while(1){
            cnt++;
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            // calc this scc's nodes here
            if (k == v)
                break;
        }
        lasv = v;
        size = cnt;
        // calc scc sub_glob here
    }
}

void run(){
    // set global val here
    stk.reserve(n);
    tim = 1;
    memset(low, 0, sizeof low);
    memset(num, 0, sizeof num);
    memset(trk, 0, sizeof trk);
    FOR(v, 1, n+1)
        if (!num[v])
            tarjan(v);
}
int color[N];
int vis = 0;

void dfs(int v){
    color[v] = 1;
    for(auto u: graph[v]){
        if (color[u] == 0)
            dfs(u);
    }
    color[v] = 2;
    vis++;
}

bool check(){
    memset(color, 0, sizeof color);
    dfs(lasv);
    return vis == n;
}

void solve() {
    cin >> n >> m;
    F0R(_, m){
        int u,v; cin >> u >> v;
        graph[u].pb(v);
    }
    run();
    if (check())
        cout << size;
    else
        cout << 0;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
