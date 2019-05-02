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

const int MOD = 998244353; //1000000007;
const ll INF = 1e18;
const int MX = 100001;
const int CF = 300005;

const int N = 5003;

int n;
int cnt[N];
ll lnv[N];
ll dp[N][N], cum[N][N];

ll mult(ll a, ll b, ll m=MOD){
    return ((a%m) * (b%m)) % m;
}
ll add(ll a, ll b, ll m=MOD){
    return (a%m + b%m) % m;
}
ll mpow(ll base, ll exp, ll m=MOD){
    ll res = 1;
    for (; exp; exp >>= 1){
        if (exp & 1)
            res = res*base % m;
        base = base*base % m;
    }
    return res;
}
ll inv(ll a, ll p=MOD){
    return mpow(a, p-2, p);
}

void inv_table(){
    FOR(i, 1, n+1)
        lnv[i] = inv(i);
}


// dp[i][j], take j cards, last with i; winning prob
// cum[i][j], \sum_{k=i}^n cnt[k] * dp[k, j];
// one can optimize space O(N), and time by 0->n instead of 0<-n
void solve() {
    cin >> n;
    F0R(_, n){
        int x; cin >> x;
        cnt[x]++;
    }
    cnt[0] = 1; // for assume start hand 
    inv_table();
    F0Rd(i, n+1){
        F0Rd(j, n+1){
            if (!cnt[i] || j == n){
                cum[i][j] = cum[i+1][j];
                continue;
            }
            ll suc = mult(cnt[i]-1, lnv[n-j]);
            ll ces = mult(cum[i+1][j+1], lnv[n-j]);
            dp[i][j] = add(suc, ces);
            //dbg(dp[i][j]);
            cum[i][j] = add(cum[i+1][j], mult(cnt[i], dp[i][j]));
        }
    }
    cout << dp[0][0];
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
