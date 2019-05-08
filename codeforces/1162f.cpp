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

const int MOD = 998244353;// 1000000007;
const ll INF = 1e18;
const int MX = 100001;
const int CF = 300005;

int n;
string s;
ll res;

ll mpow(ll base, ll exp, ll m=MOD){
    ll res = 1;
    for (; exp; exp >>= 1){
        if (exp & 1)
            res = res*base % m;
        base = base*base % m;
    }
    return res;
}

void calc(int k){
    int one = 1, zero = 0;
    int bse = 2, ase = n+2;
    int V = n+k+2;
    vi p(V); iota(all(p), 0);
    vi edge;
    // dsu
    std::function<int (int)> find = [&](int v)->int{
        return p[v] == v? v: p[v] = find(p[v]);
    };
    auto join = [&](int u, int v)->void{
        p[find(u)] = find(v);
    };
    auto check = [&](int u, int v)->bool{
        return find(u) == find(v);
    };
    // collapse 0-edge
    join(bse, 1); join(ase, 1);
    F0R(i, n)
        join(bse+i, bse+n-i-1);
    F0R(i, k)
        join(ase+i, ase+k-i-1);
    F0R(i, k){
        if (s[i] == '1')
            edge.pb(i);
        if (s[i] == '0')
            join(bse+i, ase+i);
    }
    FOR(i, k, n){
        if (s[i] == '1')
            join(bse+i, one);
        if (s[i] == '0')
            join(bse+i, zero);
    }
    // build 1-edge graph.
    if (check(one, zero)) return;
    vi graph[V];
    vi color(V, -1);
    color[find(one)] = 1;
    color[find(zero)]= 0;
    for (int i: edge){
        int u = find(bse+i);
        int v = find(ase+i);
        graph[u].pb(v);
        graph[v].pb(u);
    }
    // bfs 2-color
    F0R(i, V){
        int u = find(i);
        if (i > 2 && ~color[u])continue;
        if (!~color[u]) color[u] = 2;//any initital
        queue<int> q;
        q.push(u);
        while (!q.empty()){
            int x = q.front(); q.pop();
            for (int v: graph[x]){
                if (!~color[v]){
                    color[v] = color[x] ^ 1;
                    q.push(v);
                }
                if (color[v] == color[x])//not 2-coloring
                    return;
            }
        }
    }
    // collaspe 1-edge
    join(one, zero);
    for (int i: edge)
        join(bse+i, ase+i);
    F0R(i, V)
        find(i);
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    int C = sz(p);
    res += mpow(2, C-1);
    res %= MOD;
}

void solve() {
    cin >> s;
    n = sz(s);
    reverse(all(s));
    res = 0;
    // a-length
    FOR(k, 1, n)
        calc(k);
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
