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
int d[100000 + 5][2];

void solve() {
    ll res = 0;
    memset(d, 0, sizeof d);
    cin >> n;
    int a;
    FOR(i, 1, 2*n+1){
        cin >> a;
        if (d[a][0]){
            d[a][1] = i;
        }else{
            d[a][0] = i;
        }
    }
    res += d[1][0] + d[1][1] - 2;
    FOR(i, 1, n){
        res += abs(d[i+1][0] - d[i][0]) + abs(d[i+1][1] - d[i][1]);
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
