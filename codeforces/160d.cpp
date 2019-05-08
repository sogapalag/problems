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

int n, m;
int cnt, tim;
int sson[N];
int low[N], num[N];
int p[N];
int res[N];

struct ebge{
    int fm, to, cost, id;
} raw[N];

struct node{
    int to, bro, id;
} edge[N<<1];

void init(){
    cnt = 0;
    tim = 1;
    memset(sson, -1, sizeof sson);
    memset(low, 0, sizeof low);
    memset(num, 0, sizeof num);
    F0R(i, N){
        p[i] = i;
    }
    memset(res, 0, sizeof res);
}
// dsu
int find(int x){
    return p[x]==x? x: p[x] = find(p[x]);
}
void join(int x, int y){
    x = find(x);
    y = find(y);
    if (x==y) return;
    p[y] = x;
}
bool check(int x, int y){
    return find(x) == find(y);
}

void add_edge(int u, int v, int id){
    edge[cnt] = {v, sson[u], id};
    sson[u] = cnt++;
    edge[cnt] = {u, sson[v], id};
    sson[v] = cnt++;
}

void tarjan(int u, int fa=-1){
    low[u] = num[u] = tim++;
    for (int e=sson[u]; ~e; e=edge[e].bro){
        int v = edge[e].to;
        // here must be this, cannot use v == fa, tarjan(v, u)
        // since there'll be multi-edge, 
        // although plain graph doen't, but component graph does.
        if (e == (fa^1)) continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else{
            tarjan(v, e);
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u])//bridge
                res[edge[e].id] = 1;
        }
    }
}

void reset(int u){
    sson[u] = -1;
    low[u] = num[u] = 0;
}

// process same costs' edge, 
// which is any iff bridge in component graph.
void solve() {
    cin >> n >> m;
    F0R(i, m){
        cin >> raw[i].fm >> raw[i].to >> raw[i].cost;
        raw[i].id = i;
    }
    // kruskal
    sort(raw, raw+m, [](ebge& x, ebge& y){return x.cost < y.cost;});
    init();
    for(int i=0; i<m;){
        int cost = raw[i].cost, k = i+1;
        while (k<m && raw[k].cost == cost)
            k++;

        cnt = 0; tim = 1;
        FOR(j, i, k){
            int u = find(raw[j].fm);
            int v = find(raw[j].to);
            reset(u); reset(v);
        }
        FOR(j, i, k){
            int u = find(raw[j].fm);
            int v = find(raw[j].to);
            if (u != v){
                res[raw[j].id] = 2;
                add_edge(u, v, raw[j].id);
            }
        }
        FOR(j, i, k){
            int u = find(raw[j].fm);
            int v = find(raw[j].to);
            if (!num[u]) tarjan(u);
            //if (u!=v&&!num[v]) tarjan(v);
        }
        FOR(j, i, k){
            int x = raw[j].fm;
            int y = raw[j].to;
            int u = find(x), v = find(y);
            reset(u); reset(v);
            join(x, y);
        }
        i = k;
    }
    
    string ans[3] = {"none", "any", "at least one"};
    F0R(i, m)
        cout << ans[res[i]] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    //cout << endl;
}
