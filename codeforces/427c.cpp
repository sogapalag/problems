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

int n, m;
int cost[MX];
char color[MX];
vi ft;
map<int, multiset<int>> graph;
map<int, multiset<int>> revph;


void dfs(int v){
    color[v] = 's';
    for (auto u: graph[v]){
        if (color[u] == '0')
            dfs(u);
    }
    color[v] = 'e';
    //dbg(v);
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

ll gloc, gcnt;
int tmc, cnt;

void _dfs(int v){
    color[v] = 's';
    if (cost[v] < tmc){
        tmc = cost[v];
        cnt = 1;
    }else if (cost[v] == tmc){
        cnt += 1;
    }
    for (auto u: revph[v]){
        if (color[u] == '0')
            _dfs(u);
    }
    color[v] = 'e';
}
void scc_dfs(){
    gloc = 0; gcnt = 1;
    memset(color, '0', sizeof color);
    FORd(i, 1, n+1){
        int v = ft[i];
        // scc entry
        if (color[v] == '0'){
            tmc = MOD<<1;
            cnt = 1;
            _dfs(v);
            gloc += tmc;
            gcnt = (gcnt * cnt) % MOD;
        }
    }
}

void solve() {
    cin >> n;
    FOR(i, 1, n+1)
        cin >> cost[i];
    cin >> m;
    int x, y;
    F0R(_, m){
        cin >> x >> y;
        graph[x].insert(y);
    }

    ft.reserve(n+1); ft.pb(-1);
    full_dfs();
    rev_graph();
    scc_dfs();
    cout << gloc << ' ' << gcnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
