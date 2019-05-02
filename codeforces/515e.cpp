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
const ll INF = 1e16;
const int MX = 100005;
const int CF = 300005;

const int N = MX<<1;

int n, m;
int d[N], h[N];
ll L[N], R[N];

struct node{
    ll x, y, v;
} seg[N<<1];

void init(){
    ll cum = 0;
    n = n<<1;
    FOR(i, 1, n +1){
        seg[n+i-1].x = -cum + 2ll*h[i];
        seg[n+i-1].y =  cum + 2ll*h[i];
        seg[n+i-1].v = -INF;
        //dbg(seg[n+i-1].v);
        cum += d[i];
    }
    seg[n<<1] = {-INF, -INF, -INF};
    seg[n<<1|1] = {-INF, -INF, -INF};
}
node merge(node & L, node & R){
    node P;
    P.x = max(L.x, R.x);
    P.y = max(L.y, R.y);
    P.v = max({L.v, R.v, L.x+R.y});
    //dbg(L.x); dbg(R.x);
    //dbg(L.y); dbg(R.y);
    //dbg(L.x+R.y);
    //dbg(P.v);
    return P;
}
void build(){
    FORd(i, 1, n){
        //dbg(i);
        seg[i] = merge(seg[i<<1], seg[i<<1|1]);
    }
}

ll query(int l, int r){
    node resl{-INF, -INF, -INF};
    node resr{-INF, -INF, -INF};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        //dbg(l);
        //dbg(r);
        if (l & 1)
            resl = merge(resl, seg[l++]);
        if (r & 1)
            resr = merge(seg[--r], resr);
    }
    resl = merge(resl, resr);
    return resl.v;
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n+1){
        cin >> d[i];
        d[n+i] = d[i];
    }
    FOR(i, 1, n+1){
        cin >> h[i];
        h[n+i] = h[i];
    }
    init(); // in here n<<=1
    build();
    int a, b;
    F0R(_, m){
        cin >> a >> b;
        if (a<=b){
            a += n>>1; // add half, i.e. original n
        }
        cout << query(b, a-1) << '\n'; // tree 0-based
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    //cout << endl;
}
