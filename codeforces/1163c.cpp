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


void solve() {
    int n; cin >> n;
    vpi pt(n);
    for (auto &p: pt){
        cin >> p.f >> p.s;
    }

    auto apply = [](int & x, int & y){
        int g = __gcd(x, y);
        if (!g)
            return;
        x /= g; y /= g;
        if (x < 0){
            x *= -1; y*= -1;
        }
    };
    map<pi, set<pi>> lin;
    F0R(i, n){
        FOR(j, i+1, n){
            int dx = pt[i].f - pt[j].f;
            int dy = pt[i].s - pt[j].s;
            apply(dx, dy);
            //dbg(dx);dbg(dy);
            int h = pt[i].f * pt[j].s - pt[i].s * pt[j].f;
            int t = pt[i].f - pt[j].f;
            apply(h, t);
            if (!t)
                t = pt[i].f;
            lin[mp(dx, dy)].insert(mp(h, t));
        }
    }
    ll res = 0;
    for (auto &p: lin){
        res += sz(p.s);
    }
    res *= res;
    for (auto &p: lin){
        ll c = sz(p.s); 
        res -= c*c;
    }
    res >>= 1;
    cout << res;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
