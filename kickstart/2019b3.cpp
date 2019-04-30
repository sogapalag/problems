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
const int inf = 0x3f3f3f3f;
const int MX = 100005;
const int CF = 300005;

int n, s;
int a[MX];
vi c[MX];

int seg[MX<<2], lzy[MX<<2];
void split(int _l, int _r, int val, int p=1, int l=0, int r=MX){
    if (_r <= l || r <= _l) return;
    if (_l <= l && r <= _r){
        seg[p] += val;
        lzy[p] += val;
        return;
    }
    int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
    split(_l, _r, val, pl, l, m);
    split(_l, _r, val, pr, m, r);
    seg[p] = max(seg[pl], seg[pr]) + lzy[p];
}

// consider s=inf., when come new a_i, we add +1, to [1..i], i.e.
// 1        // after a_1
// 2, 1     // after a_2
// 3, 2, 1  // after a_3
// thus, each leaf is sum form its idx to iter(i/right), 
// note segtree, stores interval's max; 
//   where max/sum under '+' operation same group effect.
// then back to normal s!=inf, when a_i more than s, should eliminate those
// 'dist'-to-i more than s, i.e.
// 0,0,..0, -s,..-s,+1,...+1; 
// be careful not eliminate more than once, we just need to made 
// futher can't have a_i type.
//
// briefly, each i.
// we do some range '+' operation, 
//   change the prefix-sum(from [1..i] to i), changed max
// after which, total max, is exactly seg[1].
// then global update res.
void solve() {
    cin >> n >> s;
    FOR(i, 1, n+1)
        cin >> a[i];
    FOR(i, 1, n+1)
        c[i].clear();
    FOR(i, 1, n+1)
        c[a[i]].pb(i);
    memset(seg, 0, sizeof seg);
    memset(lzy, 0, sizeof lzy);
    int res = 0;;
    FOR(i, 1, n+1){
        int crt = a[i];
        split(1, i+1, 1);
        int k = lb(all(c[crt]), i) - c[crt].begin();
        if (k >= s){
            int _i = c[crt][k-s];
            split(1, _i+1, -1);
            int _l = k>s? c[crt][k-s-1] + 1 : 1;
            split(_l, _i+1, -s);
        }
        res = max(res, seg[1]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    FOR(t, 1, T+1){
        cout << "Case #" << t << ": ";
        solve();
        cout << endl;
    }
}
