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

const int N = 1e5+5;

int n;
int f[N], df[N];

void solve() {
    memset(f, 0, sizeof f);
    memset(df, 0, sizeof df);
    cin >> n;
    int mf=0;
    int res = 0;
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        df[f[x]]--;
        f[x]++;
        df[f[x]]++;
        mf = max(mf, f[x]);
        bool flag = false;
        if (df[1] == i){
            flag = true;
        }else if (df[i] == 1){
            flag = true;
        }else if (df[1] == 1 && df[mf]*mf == i-1){
            flag = true;
        }else if (df[mf-1] * (mf-1) == i - mf){
            flag = true;
        }
        if (flag)
            res = i;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
