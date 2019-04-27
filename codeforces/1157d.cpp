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

ll N, K;
ll res[MX];

void gg(){
    cout << "NO\n";
    exit(0);
}

void run(ll n, ll k, ll x, ll X){
    //dbg(n);dbg(k);dbg(x);dbg(X);
    if (!k)
        return;
    while (x < X){
        ll mid = (x+X+1)/2;
        ll tmp = mid*k + k*(k-1)/2;
        if (tmp > n){
            X = mid-1;
        }else{
            x = mid;
        }
    }
    if (k < 35){
        ll sup = x * ((1ll << k)-1);
        if (n > sup)
            gg();
    }
    res[K-k] = x;
    run(n-x, k-1, x+1, 2*x);
}


void solve() {
    cin >> N >> K;
    ll X = (N - K*(K-1)/2) / K;
    if (X < 1)
        gg();
    run(N, K, 1, X);
    cout << "YES\n";
    F0R(i, K)
        cout << res[i] << ' ';
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
