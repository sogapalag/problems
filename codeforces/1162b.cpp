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

const int N = 55;

int n, m;
int a[N][N], b[N][N];

void gg(){
    cout << "Impossible\n";
    exit(0);
}

void solve() {
    cin >> n >> m;
    F0R(i, n)
        F0R(j, m)
            cin >> a[i][j];
    F0R(i, n)
        F0R(j, m)
            cin >> b[i][j];
    F0R(i, n)
        F0R(j, m)
            if (a[i][j] > b[i][j])
                swap(a[i][j], b[i][j]);
    F0R(i, n)
        F0R(j, m-1)
            if (a[i][j] >= a[i][j+1] || b[i][j] >= b[i][j+1])
                gg();
    F0R(j, m)
        F0R(i, n-1)
            if (a[i][j] >= a[i+1][j] || b[i][j] >= b[i+1][j])
                gg();
    cout << "Possible";
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
