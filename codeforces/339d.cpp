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

const int N = (1<<17) + 5;
int e, m;
int n;
int blz; // = __builtin_clz(n);
int a[2 * N];

void build(){
    int dif;
    FORd(i, 1, n){
        dif = __builtin_clz(i) - blz;
        if (dif & 1){
            a[i] = a[i<<1] | a[i<<1|1];
        }else{
            a[i] = a[i<<1] ^ a[i<<1|1];
        }
    }
}

void upd(int p, int val){
    int dif;
    for (a[p += n] = val; p > 1; p >>= 1){
        dif = __builtin_clz(p>>1) - blz;
        if (dif & 1){
            a[p>>1] = a[p] | a[p^1];
        }else{
            a[p>>1] = a[p] ^ a[p^1];
        }
    }
}

void solve() {
    cin >> e >> m;
    n = 1 << e;
    FOR(i, n, n<<1){
        cin >> a[i];
    }
    blz = __builtin_clz(n);
    build();
    int p, b;
    F0R(i, m){
        cin >> p >> b;
        upd(p-1, b);
        cout << a[1] << endl;
    }
}

int main() {
    solve();
}
