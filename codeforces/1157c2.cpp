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

const int N = 2*1e5 + 5;

int n;
int a[N];

void solve() {
    cin >> n;
    FOR(i, 1, n+1)
        cin >> a[i];
    int l = 1, r = n;
    string res; res.reserve(n);
    int crt = 0;
    while (l <= r){
        if (a[l] <= crt && a[r] <= crt){
            break;
        }
        if (a[l] != a[r]){
            if (a[l] < a[r]){
                if (crt < a[l]){
                    res += 'L';
                    crt = a[l++];
                }else{
                    res += 'R';
                    crt = a[r--];
                }
            }else{
                if (crt < a[r]){
                    res += 'R';
                    crt = a[r--];
                }else{
                    res += 'L';
                    crt = a[l++];
                }
            }
        }else{
            ///  one way till end
            string LL; LL.reserve(r-l+1);
            string RR; RR.reserve(r-l+1);
            int l_crt = crt;
            int r_crt = crt;
            int tl = l, tr = r;
           // dbg(crt);
           // dbg(l);
           // dbg(r);
            while (tl <= r){
                if (a[tl] <= l_crt)
                    break;
                LL += 'L';
                l_crt = a[tl++];
            }
            while (l <= tr){
                if (a[tr] <= r_crt)
                    break;
                RR += 'R';
                r_crt = a[tr--];
            }
            if (sz(LL) < sz(RR)){
                res += RR;
            }else{
                res += LL;
            }
            break; // ends
        }
    }
    cout << sz(res) << '\n';
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
