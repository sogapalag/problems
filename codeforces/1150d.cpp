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

const int inf = 0x3f3f3f3f;

// dp[i][j][k], i,j,k repre length of each. dp, the minimum valid length.
// bok[c][len], letter c first occur after len, 
// upd func for more info.

int n, q;
char wu[100005];
char s[3][256];
int bok[26][100005];
int dp[256][256][256];
int I, J, K;
void init(){
    //memset(bok, inf, sizeof bok);
    memset(dp, inf, sizeof dp);
    I = J = K = 0;
    dp[0][0][0] = 0;
    F0R(i, 26){
        char c = 'a' + i;
        int tmp = inf;
        F0Rd(j, n+1){
            bok[i][j] = tmp;
            if (wu[j] == c)
                tmp = j;
            //cout << bok[i][j] << ' ';
        }
    }
}
void check(int y){
    //dbg(y);
    if (y <= n)
        cout << "YES\n";
    else
        cout << "NO\n";
}

inline void upd(int i, int j, int k){
    int tmp = inf;
    int len;
    if (i){
        len = dp[i-1][j][k];
        if (len < n)
            tmp = min(bok[s[0][i] - 'a'][len], tmp);
    }
    if (j){
        len = dp[i][j-1][k];
        if (len < n)
            tmp = min(bok[s[1][j] - 'a'][len], tmp);
    }
    if (k){
        len = dp[i][j][k-1];
        if (len < n)
            tmp = min(bok[s[2][k] - 'a'][len], tmp);
    }
    dp[i][j][k] = tmp;
}


void request(){
    //char req[10];
    char op; int x;
    //cin >> req;
    cin >> op >> x;
    //dbg(op);
    //dbg(x);
    if (op == '-'){
        if (x == 1)
            check(dp[--I][J][K]);
        if (x == 2)
            check(dp[I][--J][K]);
        if (x == 3)
            check(dp[I][J][--K]);
        return;
    }
    char c;
    cin >> c;
    //dbg(c);
    if (x == 1){
        I++;
        s[x-1][I] = c;
        F0R(j, J+1)
            F0R(k, K+1)
                upd(I, j, k);
    }
    if (x == 2){
        J++;
        s[x-1][J] = c;
        F0R(i, I+1)
            F0R(k, K+1)
                upd(i, J, k);
    }
    if (x == 3){
        K++;
        s[x-1][K] = c;
        F0R(i, I+1)
            F0R(j, J+1)
                upd(i, j, K);
    }
    check(dp[I][J][K]);
}

void solve() {
    cin >> n >> q;
    wu[0] = '#';
    cin >> (wu+1);
    //cout << "YES\n";
    init();
    F0R(_, q)
        request();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    //cout << endl;
}
