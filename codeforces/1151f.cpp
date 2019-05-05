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

const int COL = 55;
int n; ll k;
int a[111];
ll A[COL][COL];

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

// A = A X B, 0-based, n:dim
void mat_mult(ll n, ll A[][COL], ll B[][COL]){
    ll res[n][n];
    F0R(i, n){
        F0R(j, n){
            res[i][j] = 0;
            F0R(k, n){
                res[i][j] += A[i][k] * B[k][j];
                if (res[i][j] >= MOD)
                    res[i][j] %= MOD;
            }
        }
    }
    F0R(i, n)
        F0R(j, n)
            A[i][j] = res[i][j];
}

// A = A^exp, n:dim
void mat_pow(ll n, ll A[][COL], ll exp){
    ll res[n][COL];
    memset(res, 0, sizeof res);
    F0R(i, n)
        res[i][i] = 1;
    for(; exp; exp >>= 1){
        if (exp & 1)
            mat_mult(n, res, A);
        mat_mult(n, A, A);
    }
    F0R(i, n)
        F0R(j, n)
            A[i][j] = res[i][j];
}

// consider [1..cnt] #not valid bits.
void solve() {
    cin >> n >> k;
    FOR(i, 1, n+1)
        cin >> a[i];
    int cnt = 0;
    FOR(i, 1, n+1)
        if (!a[i])
            cnt++;
    int s = 0;
    FOR(i, 1, cnt+1)
        if (!a[i])
            s++;
    s = cnt - s;
    int d = min(cnt, n-cnt);

    ll q = n*(n-1)/2;
    memset(A, 0, sizeof A);
    F0R(i, d+1){
        ll tmp = q;
        if (i>0)
            A[i-1][i] = i*i, tmp-=i*i;
        if (i<d)
            A[i+1][i] = (cnt-i)*(n-cnt-i), tmp-=A[i+1][i];
        A[i][i] = tmp;
    }

    mat_pow(d+1, A, k);
    ll P = A[0][s];
    ll iq = inv(q);
    ll iQ = mpow(iq, k);
    ll res = mult(P, iQ);
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
