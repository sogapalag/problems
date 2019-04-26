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
const int MX = 100001;
const int CF = 300005;

const int N = 2*1e5+5;
int n;
int a[N];
int id;
map<int, set<int>> graph;
queue<int> q;

void gg(){
    cout << "No\n";
    exit(0);
}

void bfs(){
    while (!q.empty()){
        int vtx = q.front();
        q.pop();
        int len = sz(graph[vtx]);
        F0R(_, len){
            int nei = a[id++];
            auto it = graph[vtx].find(nei);
            if (it == graph[vtx].end())
                gg();
            graph[nei].erase(vtx);
            q.push(nei);
        }
    }
    cout << "YES";
}

void solve() {
    cin >> n;
    int x, y;
    FOR(i, 1, n){
        cin >> x >> y;
        graph[x].insert(y);
        graph[y].insert(x);
    }
    FOR(i, 1, n+1)
        cin >> a[i];

    q.push(1);  id = 1;
    if (a[id++] != 1)
        gg();
    bfs();
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
