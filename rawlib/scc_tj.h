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

///////////////////////////////////////////////
//    tarjan
//    since sccs DAG, imagine last scc' root, 
//    would be iff low==num, and nodes in this scc, same low.
//
//    NOTE: nodes not [1..n] index, need some fix.


int n; // nodes [1..n]

int tim; 
int low[MX];
int num[MX];
bool trk[MX];
vi stk;
map<int, multiset<int>> graph;


//ll gloc, gcnt;

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
        while(1){
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            // calc this scc's nodes here
            if (k == v)
                break;
        }
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

void solve() {
    run();
}
