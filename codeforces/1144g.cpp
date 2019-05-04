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

#define __seg_p (int _l, int _r, int val, int p=1, int l=0, int r=N)
#define __seg_out if (_r <= l || r <= _l)
#define __seg_in if (_l <= l && r <= _r)
#define __seg_one if (l+1 == r)
#define __seg_calc int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
#define __seg_l (_l, _r, val, pl, l, m)
#define __seg_r (_l, _r, val, pr, m, r)

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100005;
const int CF = 300005;

const int N = 2e5+5;

int n;
int a[N];

void gg(){
    cout << "NO" << endl;
    exit(0);
}

void solve() {
    cin >> n;
    FOR(i, 1, n+1)
        cin >> a[i];
    if (n == 1){
        cout << "YES\n";
        cout << "1"; return;
    }
    vi inc, dec;
    if (a[1] == a[2]){
        inc.pb(1);
        dec.pb(2);
    }else if(a[1] < a[2]){
        inc.pb(1); inc.pb(2);
    }else{
        dec.pb(1); dec.pb(2);
    }
    int i = 3;
    while (i<=n){
        if (dec.empty()){
            int u = a[inc.back()];
            if (a[i] > u){
                inc.pb(i);
            }else{
                int dori = inc.back();
                inc.pop_back(); dec.pb(dori);
                continue;
            }
        }else if (inc.empty()){
            int d = a[dec.back()];
            if (a[i] < d){
                dec.pb(i);
            }else{
                int uori = dec.back();
                dec.pop_back(); inc.pb(uori);
                continue;
            }
        }else{
            int d = a[dec.back()], u = a[inc.back()];
            if (u < d){ // not crossed
                if (a[i] <= u){
                    dec.pb(i);
                }else if (a[i] >= d){
                    inc.pb(i);
                }else{ // in the middle
                    if (i == n){
                        inc.pb(i);
                    }else{
                        if (a[i+1] <= u){// give inc more free
                            dec.pb(i);  dec.pb(i+1);
                        }else if (a[i+1] >= d){// give dec more free
                            inc.pb(i);  inc.pb(i+1);
                        }else{
                            if (a[i] < a[i+1]){
                                inc.pb(i); // al least
                            }else {
                                dec.pb(i);
                            }
                            i--;
                        }
                        i++;
                    }
                }
            }else{//crossed
                if (a[i] < d){
                    dec.pb(i);
                }else if (a[i] > u){
                    inc.pb(i);
                }else{
                    gg();
                }
            }
        }
        i++;
    }

    char c[N];
    for (auto i: inc)
        c[i] = '0';
    for (auto i: dec)
        c[i] = '1';
    if (inc.empty())
        c[1] = '0';
    if (dec.empty())
        c[1] = '1';

    cout << "YES\n";
    FOR(i, 1, n+1)
        cout << c[i] << ' ';
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    cout << endl;
}
