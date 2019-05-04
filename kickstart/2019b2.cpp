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

const int N = 103;
const int M = 1e4+4;

int n;
int s[N], e[N], l[N];
int id[N];

int dp[N][M];

void solve() {
    cin >> n;
    FOR(i, 1, n+1){
        cin >> s[i] >> e[i] >> l[i];
        id[i] = i;
    }
    sort(id+1, id+n+1, [](int x, int y){
            return s[x] * l[y] < s[y] * l[x];
            });
    memset(dp, 0, sizeof dp);
    FORd(i, 1, n+1){
        int x = id[i];
        int dt = s[x];
        FORd(t, 0, M){
            int val = dp[i+1][t+dt] + max(0, e[x] - l[x]*t);
            dp[i][t] = max(dp[i+1][t], val);
        }
    }
    cout << dp[1][0];
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int T; cin >> T;
    FOR(t, 1, T+1){
        cout << "Case #" << t << ": ";
        solve();
        cout << endl;
    }
}
