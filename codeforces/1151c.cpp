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


void solve() {
    ll l, r;
    cin >> l >> r;

    auto pos = [](ll x){
        int d = 63 - __builtin_clzll(x);
        ll odd = 0, even = 0;
        FOR(i, 0, d){
            if (i&1)
                even += 1ll << i;
            else
                odd += 1ll << i;
        }
        if (d&1)
            even += x - (1ll << d) + 1;
        else
            odd += x - (1ll << d) + 1;
        //assert(odd + even, x);
        return mp(odd, even);
    };
    auto f = [](ll x){
        return (x%MOD)*(x%MOD) %MOD;
    };
    auto g = [](ll x){
        return (x%MOD)*((x+1)%MOD) %MOD;
    };
    auto sum = [&](ll x){
        if (!x) return 0ll;
        auto p = pos(x);
        ll s = f(p.f) + g(p.s);
        return s%MOD;
    };
    ll res = sum(r) - sum(l-1);
    res = (res + MOD) % MOD;
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
