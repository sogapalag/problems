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
const int MX = 100005;
const int CF = 300005;

int n;
ll k;
int a[MX];
ll rig[MX];

void solve() {
    cin >> n >> k;
    FOR(i, 1, n+1)
        cin >> a[i];
    Tree<pi> sr;
    rig[n+1] = 0;
    FORd(i, 1, n+1){
        int tmp = a[i];
        rig[i] = rig[i+1] + sr.order_of_key(mp(tmp, 0));
        sr.insert(mp(tmp, i));
    }
    Tree<pi> sl;
    ll res = 0, crt = rig[1];
    if (crt <= k){
        ll t = n;
        res = t*(t-1)/2;
        cout << res;
        return;
    }
    pi tmp = mp(a[1], 1);
    sl.insert(tmp); sr.erase(tmp);
    int i=1, j=2;
    while (i<n){
        while (crt > k && j <= n){
            crt -= rig[j] - rig[j+1];
            crt -= i - sl.order_of_key(mp(a[j], MX));
            sr.erase(mp(a[j], j));
            j++;
        }
        if (j>n)
            break;
        res += n-j+1;
        crt += i - sl.order_of_key(mp(a[i+1], MX));
        crt += sr.order_of_key(mp(a[i+1], 0));
        i++;
        sl.insert(mp(a[i], i));
    }
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
