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

int n;
int a[111];

void gg(){
    cout << "Infinite\n";
    exit(0);
}

void solve() {
    cin >> n;
    FOR(i, 1, n+1)
        cin >> a[i];
    a[0] = -1;
    int res = 0;
    int i = 2;
    for (;i<=n;i++){
        if (a[i] == a[i-1])
            gg();
        if (a[i-1] == 1){ //cir
            if (a[i] == 2){
                res += 3;
                if (a[i-2] == 3)
                    res -= 1;
            }else{
                res += 4;
            }
        }else if (a[i-1] == 2){//tri
            if (a[i] == 1)
                res += 3;
            else
                gg();
        }else{ // sq=3
            if (a[i] == 1)
                res += 4;
            else
                gg();
        }
    }
    cout << "Finite\n";
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
