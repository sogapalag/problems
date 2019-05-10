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

#define dbg(x) cerr<<#x<<" = "<<(x)<<endl;
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
const int MX = 100001;
const int CF = 300005;

const int C = 1005, S = 55, T = 55;
int lc, ls, lt;
char c[C], s[S], t[T];
int bac_s[S][26], bac_t[T][26];

void kmp(int l, char p[], int bac[][26]){
    int b[S]; b[0]=-1;// kmp backup table
    int j = -1;
    for (int i=0; i < l;){
        while (j >= 0 && p[i] != p[j])
            j = b[j];
        i++; j++;
        b[i] = j;
    }

    // b[i][x]: when before matched length i, next coming char x
    // matched length
    for (int i=0; i<=l; i++){
        for (char x = 'a'; x <= 'z'; x++){
            int j = i;
            while (j >= 0 && x != p[j])
                j = b[j];
            bac[i][x - 'a'] = ++j;
        }
    }
}
// dp[i][j][k] : when length i; s,t each matched j,k; maxi val.
int dp[C][S][T];
void run_dp(){
    memset(dp, -inf, sizeof dp);
    dp[0][0][0] = 0;
    for (int i = 1; i <= lc; i++){
        for (int j = 0; j <= ls; j++){
            for (int k = 0; k <= lt; k++){
                for (char x = 'a'; x <= 'z'; x++){
                    if (c[i] == '*' || c[i] == x){
                        int _j = bac_s[j][x - 'a'];
                        int _k = bac_t[k][x - 'a'];
                        int tmp = dp[i-1][j][k] + (_j == ls) - (_k == lt);
                        dp[i][_j][_k] = max(dp[i][_j][_k], tmp);
                    }
                }
            }
        }
    } 
    int res = -inf;
    for (int j = 0; j <= ls; j++){
        for (int k = 0; k <= lt; k++){
            res = max(res, dp[lc][j][k]);
        }
    }
    cout << res;
}

void solve() {
    cin >> (c+1) >> (s+1) >> (t+1);
    lc = strlen(c+1), ls = strlen(s+1), lt = strlen(t+1);
    kmp(ls, s+1, bac_s);
    kmp(lt, t+1, bac_t);
    run_dp();
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
