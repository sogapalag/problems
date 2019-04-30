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

const int N = 2e5 + 10;

int n;

char op[10];
char o[N];
int x[N], y[N];
set<int> s[N];

int seg[N<<2];
void split(int _l, int _r, int val, int p=1, int l=0, int r=N){
    if (_r <= l || r <= _l) return;
    if (_l <= l && r <= _r){
        seg[p] = val;
        return;
    }
    int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
    split(_l, _r, val, pl, l, m);
    split(_l, _r, val, pr, m, r);
    seg[p] = max(seg[pl], seg[pr]);
}

int query(int _l, int _r, int val, int p=1, int l=0, int r=N){
    if (_r <= l || r <= _l) return inf;
    if (l+1 == r){
        if (seg[p] >= val)
            return l;
    }
    if (seg[p] < val)
        return inf;
    int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
    int ql = query(_l, _r, val, pl, l, m);
    if (ql < inf)
        return ql;
    int qr = query(_l, _r, val, pr, m, r);
    return qr;
}

// x- 10^9 need map to [N]
// each leaf, store set of y
// segtree, store max of intervals' ys
void solve() {
    cin >> n;
    Tree<int> map;
    FOR(i, 1, n+1){
        scanf("%s%d%d", op, &x[i], &y[i]);
        o[i] = op[0];
        map.insert(x[i]);
    }
    memset(seg, -inf, sizeof seg);
    FOR(i, 1, n+1){
        int _x = map.order_of_key(x[i]);
        if (o[i] == 'a'){
            s[_x].insert(y[i]);
            int _y = *s[_x].rbegin();
            split(_x, _x+1, _y);
        }
        if (o[i] == 'r'){
            s[_x].erase(y[i]);
            int _y = s[_x].empty() ? -inf : *s[_x].rbegin();
            split(_x, _x+1, _y);
        }
        if (o[i] == 'f'){
            int _ix = query(_x+1, N, y[i]+1);
            if (_ix < inf){
                int xx = *map.find_by_order(_ix);
                int yy = *s[_ix].lb(y[i] + 1);
                //cout << xx << ' ' << yy << '\n';
                printf("%d %d\n", xx, yy);
            }else{
                // old problem has some format error.
                //cout << "-1\n";
                printf("-1\n");
            }
        }
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    //cout << endl;
}
