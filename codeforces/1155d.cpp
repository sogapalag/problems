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

int n, x;
ll a[CF];
// space could O(1)
// dp[i][0..=2], end with i, 0: still not use x; 1: using x; 2: can't use x.
ll dp[CF][3];

void solve() {
    cin >> n >> x;
    FOR(i, 1, n+1){
        cin >> a[i];
    }
    ll res = 0;
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    FOR(i, 1, n+1){
        dp[i][0] = max(dp[i-1][0] + a[i], a[i]);
        ll ax = a[i] * x;
        dp[i][1] = max({dp[i-1][0] + ax, dp[i-1][1] + ax, ax});
        dp[i][2] = max({dp[i-1][1] + a[i], dp[i-1][2] + a[i], a[i]});
        res = max({res, dp[i][0], dp[i][1], dp[i][2]});
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
