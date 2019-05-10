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


// another related problem https://atcoder.jp/contests/agc031/tasks/agc031_c
// check out gray code;
// note ^ form linear algebra.
// why add func work? 
// 000001
// 00001X
// 0001XX
// 001XXX
// 01XXXX
// 1XXXXX
// form a basis.(by induction proof)
// vec also form a basis.
void solve() {
    int n; cin >> n;
    vi s(n);
    for (int &x:s)
        cin >> x;
    sort(all(s));
    vi basis, vec;
    auto add = [&](int u){
        int tmp = u;
        for (int& v: basis)
            u = min(u, u^v);
        if (u > 0){
            basis.pb(u);
            vec.pb(tmp);
        }
    };
    auto gray = [&](int dim){
        assert(sz(vec) == dim);
        vi res(1<<dim); res[0] = 0;
        for (int d = 0; d < dim; d++){
            int crt = 1 << d;//crt size
            //dbg(vec[d]);
            for (int j = 0; j < crt; j++)
                res[j+crt] = res[crt-j-1] ^ vec[d];
        }
        cout << dim << '\n';
        for (int& y: res)
            cout << y << ' ';
    };
    int j = 0;
    int dim = 0;
    for (int x = 0; x < 20; x++){
        for (;j < n && s[j] < (1<<x); j++)
            add(s[j]);
        if (sz(basis) == x)
            dim = x;
    }
    basis.clear(); vec.clear();
    for (j=0; j < n && s[j] < (1<<dim); j++)
        add(s[j]);
    gray(dim);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
