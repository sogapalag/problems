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

int n, m;
int res[300000+5];

// TreeSet
void solve() {
    cin >> n >> m;
    set<int> alive;
    FOR(i, 1, n+1){
        alive.insert(i);
    }
    FOR(i, 1, m+1){
        int l, r, x;
        cin >> l >> r >> x;
        auto it = alive.lb(l);
        vi los;
        while (it != alive.end()){
            int k = *it;
            if (k > r){
                break;
            }
            if (k != x){
                los.pb(k);
                res[k] = x;
            }
            it++;
        }
        for (auto &k: los){
            alive.erase(k);
        }
    }
    FOR(i, 1, n+1){
        cout << res[i] << ' ';
    }
}

int main() {
    solve();
    cout << endl;
}
