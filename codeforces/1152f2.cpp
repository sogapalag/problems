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


////////////////////////////////////////////
// b^e, b^-1, A^e, A*B; with mod.
//
//
//
////////////////////////////////////////////

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
const int COL = 13*16 + 2; // k+1 X #msk
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

int n, k, m;

ll A[COL][COL];

void solve() {
    cin >> n >> k >> m;
    // express k X msk space flat.
    memset(A, 0, sizeof A);
    int w = k+1; //width
    // init trans mat
    F0R(msk, 1<<m){
        F0R(t, k+1){
            A[(msk>>1)*w + t][msk*w + t] += 1;
            if (t != k)
                A[(msk>>1 | 1<<(m-1))*w + t+1][msk*w + t] += 
                    1 + __builtin_popcount(msk);
        }
    }
    int dim = (1<<m) * w;
    mat_pow(dim, A, n);
    // since init state, (1,0,...0), A[.][0] is final
    ll res = 0;
    F0R(msk, 1<<m)
        res = add(res, A[msk*w + k][0]);
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
