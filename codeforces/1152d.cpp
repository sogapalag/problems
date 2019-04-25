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

const int N = 1005;
int n;
int dp[N];

// catalan triangle
// https://en.wikipedia.org/wiki/Catalan%27s_triangle
// sum of index at (i+j) = 1 (mod 2)
void solve() {
    cin >> n;
    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    int res = 0;
    FOR(i, 1, n+1){
        FOR(j, 0, i+1){
            if (j)
                dp[j] = (dp[j-1] + dp[j]) % MOD;
            if ((i+j) & 1)
                res = (res + dp[j]) % MOD;
        }
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
