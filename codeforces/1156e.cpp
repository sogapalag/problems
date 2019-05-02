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
int a[N];
int id[N];
pi seg[N<<1];

void build(){
    FORd(i, 1, n)
        seg[i] = max(seg[i<<1], seg[i<<1|1]);
}

int query(int l, int r){
    pi res{-1e9, 0};
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l&1)
            res = max(res, seg[l++]);
        if (r&1)
            res = max(res, seg[--r]);
    }
    return res.s;
}

int ans_in(int l, int r){
    if (r-l < 3) return 0;
    int p = query(l, r);
    int res = 0;
    if (p-l < r-p){
        FOR(i, l, p){
            int k = id[a[p] - a[i]]; 
            res += (p<k && k<r)? 1 : 0;
        }
    }else{
        FOR(i, p+1, r){
            int k = id[a[p] - a[i]];
            res += (l<=k && k<p)? 1 : 0;
        }
    }
    return res + ans_in(l, p) + ans_in(p+1, r);
}

// max-seg, with store id
// iter the smaller half.
// divide & conqure
void solve() {
    cin >> n;
    int x;
    F0R(i, n){
        cin >> x;
        a[i] = x;
        id[x] = i;
        seg[n+i] = {x, i};
    }
    build();
    cout << ans_in(0, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
