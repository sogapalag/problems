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
    const int N = 1e5+5;
    int n; cin >> n;
    vi u(n);
    for (int &x: u)
        cin >> x;
    
    vi cnt(N, 0);
    for (int &x: u)
        cnt[x]++;
    map<int, set<int>> r;
    F0R(i, N){
        if (cnt[i]){
            r[cnt[i]].insert(i);
        }
    }
    auto valid = [&](){
        if (sz(r)>2)
            return false;
        if (sz(r) == 1){
            auto  it = r.begin();
            if (it->f == 1 || sz(it->s) == 1)
                return true;
            return false;
        }
        if (sz(r) == 2){
            auto it = r.begin();
            //dbg(it->f);
            auto jt = r.begin(); jt++;
            if (it->f == 1 && sz(it->s) == 1)
                return true;
            if (jt->f - it->f == 1 && sz(jt->s) == 1)
                return true;
            return false;
        }
    };
    F0Rd(i, n){
        if (valid()){
            cout << (i+1);
            return;
        }
        int x = u[i];
        int k = cnt[x];
        r[k].erase(x);
        if (r[k].empty())
            r.erase(k);
        k--; cnt[x]--;
        //dbg(k);
        if (k)
            r[k].insert(x);
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
