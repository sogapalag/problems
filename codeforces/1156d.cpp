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

const int N = 2e5+5;
int n;
int p[2][N], r[2][N];

int find(int x, int c){
    return p[c][x] == x? x: p[c][x] = find(p[c][x], c);
}
void join(int x, int y, int c){
    x = find(x, c);
    y = find(y, c);
    if (r[c][x] < r[c][y])
        swap(x, y);
    p[c][y] = x;
    r[c][x] += r[c][y];
}

void init(){
    FOR(i, 1, n+1){
        p[0][i] = p[1][i] = i;
        r[0][i] = r[1][i] = 1;
    }
}

// dsu
void solve() {
    cin >> n;
    init();
    int x, y, c;
    F0R(_, n-1){
        cin >> x >> y >> c;
        join(x, y, c);
    }
    ll res = 0;
    FOR(i, 1, n+1){
      //  if (p[0][i] == i)
      //      res += 1ll * r[0][i] * (r[0][i] - 1);
      //  if (p[1][i] == i)
      //      res += 1ll * r[1][i] * (r[1][i] - 1);
      //  res += 1ll * (r[0][find(i, 0)] - 1) * (r[1][find(i, 1)] - 1);
      //  equavlent to above
        res += 1ll * r[0][find(i, 0)] * r[1][find(i, 1)] - 1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
