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

#define dbg(x) cout<<#x<<'='<<(x)<<endl;

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

const int N = 1e5 + 5;
int n;
int b[N];
int c[N];
vi res;

map<int, multiset<int>> graph;

void gg(){
    cout << -1 << '\n';
    exit(0);
}

void build(){
    FOR(i, 1, n){
        if (b[i] > c[i])
            gg(); // not follow problem description.
        graph[b[i]].insert(c[i]);
        graph[c[i]].insert(b[i]);
    }
}

int entry(){
    int cnt = 0; // count #odd degree
    int res = b[1];
    for (auto &v: graph){
        if (sz(v.s) & 1){
            cnt += 1;
            res = v.f;
        }
    }
    if (cnt > 2)
        gg(); // entry candidate. > 2
    return res;
}

// Hierholzer’s
void dfs(int vtx){
    while (!graph[vtx].empty()){
        auto it = graph[vtx].begin();
        int nei = *it;
        graph[vtx].erase(it);            // crash if it = rit
        auto rit = graph[nei].find(vtx); // must below above line
        graph[nei].erase(rit); // if val, will erase all; we only one.
        dfs(nei);
    }
    res.pb(vtx); //a reverse chain. however valid
}

void print(){
    if (sz(res) != n)
        gg(); // not connected
    for (auto k: res)
        cout << k << ' ';
}

// we imagine(view) each (b,c) pair is a rope(edge), 
// valid iff put thes pair in a line, i.e. a1-a2, a2-a3, ..., a_{n-1}-a_n
//           which, conj-node must be same value.
// That we construct graph with, edges b--c,
//                               nodes {bs, cs} i.e. merge same value
//                                 e.g. if b1=c1=5, node with self-loop-edge
//                                  if b1=b2, or b1=c3, put together.
// aka, we glue ropes with same value. after that, each vertex distinct val.
// then an Euler path <=> loose some glue form a line.
// with thm each degree even(aka, in-to-out), except entry(end).
// with verify path length, i.e. connectivity.
void solve() {
    cin >> n;
    FOR(i, 1, n)
        cin >> b[i];
    FOR(i, 1, n)
        cin >> c[i];

    build();
    int ent = entry();
    res.reserve(n);
    dfs(ent);
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
