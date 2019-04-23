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

int k;
int c[N];
int s[N];
ll dp[N];
ll bino[N][N];

void bino_table(){
    F0R(i, N){
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    FOR(i, 1, N){
        FOR(j, 1, i){
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % MOD;
        }
    }
}

void solve() {
    ll res = 0;
    cin >> k;
    FOR(i, 1, k+1){
        cin >> c[i];
    }
    c[0] = 0; s[0] = 0;
    FOR(i, 1, k+1){
        s[i] = s[i-1] + c[i];
    }

    bino_table();

    dp[0] = 1;
    FOR(i, 1, k+1){
        dp[i] = dp[i-1] * bino[s[i] - 1][c[i] - 1];
        dp[i] %= MOD;
    }
    res = dp[k];
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
