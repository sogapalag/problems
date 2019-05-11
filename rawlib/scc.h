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

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100003;
const int CF = 300005;


/////////////////////////////////////////////////////
//     Kosaraju's algorithm
//  first dfs forest, get finish time order of nodes
//  second _dfs on rev-graph, with ft decrasing order
//    every loop call _dfs means enter a new scc.
/////////////////////////////////////////////////////


int n; // #nodes [1..n]
char color[MX];
vi ft; // node in finish time order
map<int, multiset<int>> graph;
map<int, multiset<int>> revph;


void dfs(int v){
    color[v] = 's';
    for (auto u: graph[v]){
        if (color[u] == '0')
            dfs(u);
    }
    color[v] = 'e';
    ft.pb(v);
}
void full_dfs(){
    memset(color, '0', sizeof color);
    FOR(v, 1, n+1){
        if (color[v] == '0')
            dfs(v);
    }
}
void rev_graph(){
    for (auto &p: graph){
        int v = p.f;
        for (auto u: p.s){
            revph[u].insert(v);
        }
    }
}

void _dfs(int v){
    color[v] = 's';
    // do something here in some node of scc.
    for (auto u: revph[v]){
        if (color[u] == '0')
            _dfs(u);
    }
    color[v] = 'e';
}
void scc_dfs(){
    memset(color, '0', sizeof color);
    FORd(i, 1, n+1){
        int v = ft[i];
        // scc entry
        if (color[v] == '0'){
            // in scc
            _dfs(v);
            // out scc
        }
    }
}

void solve() {
    ft.reserve(n+1); ft.pb(-1);
    full_dfs();
    rev_graph();
    scc_dfs();
}

