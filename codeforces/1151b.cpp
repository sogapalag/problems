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

const int N =511;
int n, m;
int a[N][N];
int d[N];

void solve() {
    cin >> n >> m;
    FOR(i, 1, n+1){
        FOR(j, 1, m+1){
            int x; cin >> x;
            a[i][j] = x;
        }
    }
    int res = 0;
    FOR(i, 1, n+1){
        res ^= a[i][1];
        d[i] = 1;
    }
    bool find = false;
    if (res == 0){
        FOR(i, 1, n+1){
            FOR(j, 2, m+1){
                if (a[i][j] != a[i][1]){
                    d[i] = j;
                    res = 1;
                    find = true; break;
                }
            }
            if (find)
                break;
        }
    }
    if (!res){
        cout << "NIE";
    }else{
        cout << "TAK\n";
        FOR(i,1,n+1)
            cout << d[i] << ' ';
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
