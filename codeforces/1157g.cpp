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

const int N = 202;

int n, m;
bool a[N][N];
bool b[N][N];
bool row[N], col[N];

void check(int x, int y){
    bool flag = false;
    FOR(i, x, y+1){
        if (flag){
            bool tmp = b[i][1];
            FOR(j, 2, m+1)
                if (tmp != b[i][j])
                    return;
            row[i] = !tmp;
        }else{
            bool tmp = b[i][1];
            int cnt = 0;
            FOR(j, 2, m+1){
                if (tmp != b[i][j]){
                    cnt += 1;
                    tmp = b[i][j];
                }
            }
            if (cnt > 1)
                return;
            row[i] = b[i][1];
            if (cnt == 1)
                flag = true;
        }
    }
    cout << "YES\n";
    FOR(i, 1, n+1){
        char c = row[i] ? '1': '0';
        cout << c;
    }
    cout << '\n';
    FOR(j, 1, m+1){
        char c = col[j] ? '1': '0';
        cout << c;
    }
    cout << '\n';
    exit(0);

}
void frow(){
    FOR(j, 1, m+1)
        col[j] = a[1][j];
    FOR(i, 1, n+1){
        FOR(j, 1, m+1){
            b[i][j] = a[i][j];
            if (col[j])
                b[i][j] = !b[i][j];
        }
    }
    row[1] = false;
    check(2, n);
}
void lrow(){
    FOR(j, 1, m+1)
        col[j] = !a[n][j];
    FOR(i, 1, n+1){
        FOR(j, 1, m+1){
            b[i][j] = a[i][j];
            if (col[j])
                b[i][j] = !b[i][j];
        }
    }
    row[n] = false;
    check(1, n-1);
}

// valid solution must be one of
//    set first row all zero
// or set last row all one.
void solve() {
    cin >> n >> m;
    FOR(i, 1, n+1){
        FOR(j, 1, m+1){
            cin >> a[i][j];
        }
    }
    frow();
    lrow();
    cout << "NO";
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
