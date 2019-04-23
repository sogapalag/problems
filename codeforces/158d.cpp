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

int n;
int t[20000 + 5];

void solve() {
    int res = INT_MIN;
    cin >> n;
    F0R(i, n){
        cin >> t[i];
    }
    vi fac;
    fac.reserve(n);
    FOR(i, 3, n+1){
        if (!(n%i)){
            fac.pb(i);
        }
    }
    int crt = 0;
    for (auto &i: fac){
        int k = n/i;
        F0R(j, k){
            crt = 0;
            int jj = j;
            while (jj < n){
                crt += t[jj];
                jj += k;
            }
            res = max(res, crt);
        }
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
