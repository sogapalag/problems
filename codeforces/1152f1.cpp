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

const int N = 100000 + 5;
const int K = 14;
const int M = 20;

int n, k, m;
int dp[N][M][K];

void add(int & res, int val){
    res = (res + val) % MOD;
}

// think in this way, (problem-seq or reversely), below is rev.
// we iter [i:0 -> n) ask whether i+1 join the path.
// if i+1 say yes, it can attach in last, 
//                  or insert beform some x with i+1 <= x+m;
// e.g. say m=4, i+1 = 18, we ask which, if insert, it can only insert
//   before exist 14, 15, 16, 17(msk tell); note them may not this order
//      i.e. may, 15, 14, 17. (but msk record relative exist to 17/18)
//      so total 1 {attach} + msk'1s {insert} ways to put i+1 in path.
//
// dp[i][msk][t]: iter till i, aka, [0, i] requested
//                msk, [i-m+1..i] in path ?
//                t: #balls in path
void solve() {
    cin >> n >> k >> m;
    dp[0][0][0] = 1;
    F0R(i, n){
        F0R(msk, 1<<m){
            F0R(t, k+1){
                if (! dp[i][msk][t])
                    continue;
                add(dp[i+1][msk>>1][t], dp[i][msk][t]);
                ll way = 1 + __builtin_popcount(msk);
                add(dp[i+1][msk>>1 | 1<<(m-1)][t+1], 
                        way * dp[i][msk][t] % MOD);
            }
        }
    }
    int res = 0;
    F0R(msk, 1<<m)
        add(res, dp[n][msk][k]);
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
