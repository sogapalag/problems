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

int N;
int S[111];
int E[111];
int L[111];
int sl[111][111];
int c[111];

void solve() {
    int res = 0;
    cin >> N;
    FOR(i, 1, N+1){
        cin >> S[i] >> E[i] >> L[i];
    }
    FOR(i, 1, N+1){
        FOR(j, 1, N+1){
            sl[i][j] = S[i] * L[j];
        }
    }
    FOR(i, 1, N+1){
        res += E[i];
    }
    int cost = 0;
    bool ok[111];
    memset(ok, 0, sizeof ok);
    FOR(k, 1, N+1){
        memset(c, 0, sizeof c);
        int m = 0;
        int tmp = 123456789;
        FOR(i, 1, N+1){
            if (!ok[i]){
                FOR(j, 1, N+1){
                    if (!ok[j] && i!=j){
                        c[i] += min(sl[i][j], E[j]);
                    }
                }
                if (tmp > c[i]){
                    tmp = c[i];
                    m = i;
                }
            }
        }
        cost += tmp;
        ok[m] = true; E[m] = 0;
        FOR(j, 1, N+1){
            if (!ok[j]){
                if (E[j] <= sl[m][j]){
                    ok[j] = true; E[j] = 0;
                    k += 1;
                }
                else{
                    E[j] -= sl[m][j];
                }
            }
        }
    }
    res -= cost;
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
