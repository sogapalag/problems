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
const ll INF = 1e18;
const int MX = 100005;
const int CF = 300005;

const int N = 1e4+4;

int n;
ll a[N];

int PRIME[4] = {2, 3, 5, 7};

vpi decomp(ll num){
    vpi be;
    for (auto p: PRIME){
        if (p*p > num)
            break;
        int exp = 0;
        while (num % p == 0){
            exp += 1;
            num /= p;
        }
        if (exp != 0)
            be.pb(mp(p, exp));
    }
    if (num != 1)
        be.pb(mp(num, 1));
    return be;
}

void calc(ll x){
    vpi be = decomp(x);
    ll res = 1;
    for (auto &p: be){
        if (p.f>2){
            ll tmp = pow(1ll * p.f, 1ll + p.s);
            res *= (tmp-1)/(p.f-1);
        }
    }
    cout << res << '\n';
}

void solve() {
    cin >> n;
    FOR(i, 1, n+1)
        cin >> a[i];
    FOR(i, 1, n+1)
        calc(a[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    //cout << endl;
}
