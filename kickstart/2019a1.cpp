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

int N, P;
int s[100000 + 5];

void solve() {
    int res = 0;
    memset(s, 0, sizeof s);
    cin >> N >> P;
    FOR(i, 1, N+1) cin >> s[i];
    sort(s+1, s+N+1, greater<int>());
    int crt = s[1] * P;
    FOR(i, 1, P+1) crt -= s[i];
    res = crt;
    FOR(i, 2, N-P+2){
        crt += s[i] - s[i+P-1] - (P-1) * (s[i-1] - s[i]);
        res = min(res, crt);
    }
    cout << res;
}

int main() {
    int T; cin >> T;
    FOR(i,1,T+1) {
        cout << "Case #" << i << ": ";
        solve();
        cout << endl;
    }
}
