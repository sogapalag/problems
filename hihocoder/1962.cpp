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
const int inf = 0x3f3f3f3f;
const int MX = 100005;
const int CF = 300005;

const int N = 256;
int n, m;
int s[N], e[N], w[N];
int id[N];

const int V = 512;
const int E = 512<<2;
int sson[V], pre[V], dis[V], trk[V];
int cnt;

struct node{
    int to, bro, cap, flow, cost;
} edge[E];

void init(){
    cnt = 0;
    memset(sson, -1, sizeof sson);
}

void add_edge(int u, int v, int cap, int cost){
    edge[cnt] = {v, sson[u], cap, 0, cost};
    sson[u] = cnt++;
    edge[cnt] = {u, sson[v], 0, 0, -cost};
    sson[v] = cnt++;
}

bool spfa(int s, int t){
    queue<int> q;
    memset(pre, -1, sizeof pre);
    memset(dis, inf, sizeof dis);
    memset(trk, 0, sizeof trk);
    dis[s] = 0; trk[s] = 1; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop(); trk[u] = 0;
        for (int e=sson[u]; ~e; e=edge[e].bro){
            int v = edge[e].to;
            if (edge[e].cap > edge[e].flow && dis[v] > dis[u] + edge[e].cost){
                dis[v] = dis[u] + edge[e].cost;
                pre[v] = e;
                if (!trk[v]){
                    trk[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return pre[t] != -1;
}

pi mcmf(int s, int t){
    int flow = 0, cost = 0;
    while (spfa(s, t)){
        int f = inf;
        for (int e=pre[t]; ~e; e=pre[edge[e^1].to])
            f = min(f, edge[e].cap - edge[e].flow);
        for (int e=pre[t]; ~e; e=pre[edge[e^1].to]){
            edge[e].flow += f;
            edge[e^1].flow -= f;
            cost += edge[e].cost * f;
        }
        flow += f;
    }
    return {flow, cost};
}

// s ->(m,0) -> time_i->(inf,0) ...-> t_end -> (k,0) t;
// each task, find correspoding time_s -> time_e add ->(1, -w);
// thus a min cost flow problem.
void solve() {
    cin >> n >> m;
    vi vtx;
    FOR(i,1,n+1){
        cin >> s[i] >> e[i] >> w[i];
        vtx.pb(s[i]);
        vtx.pb(e[i]);
    }
    sort(all(vtx));
    vtx.erase(unique(all(vtx)), vtx.end());

    int S = 0;
    int T = sz(vtx) + 1;

    init();
    FOR(i, 1, T-1)
        add_edge(i, i+1, inf, 0);
    add_edge(S, 1, m, 0);
    add_edge(T-1, T, m, 0);
    FOR(i, 1, n+1){
        int u = lb(all(vtx), s[i]) - vtx.begin();
        int v = lb(all(vtx), e[i]) - vtx.begin();
        add_edge(u, v, 1, -w[i]);
    }
    pi res = mcmf(S, T);
    cout << -res.s;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
