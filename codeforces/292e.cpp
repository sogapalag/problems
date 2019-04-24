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
const int CF = 300005;

const int N = 1e5 + 5;
int n, m;
int a[N];
int b[N];
int oft[N];
int tr[2 * N];

// range assign
void upd(int l, int r, int val){
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            tr[l++] = val;
        if (r & 1)
            tr[--r] = val;
    }
}
// max
int query(int p){
    int tmp = 0;
    for (p += n; p > 0; p >>= 1)
        tmp = max(tmp, tr[p]);
    return tmp;
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n+1){
        cin >> a[i];
    }
    FOR(i, 1, n+1){
        cin >> b[i];
    }
    memset(tr, 0, sizeof tr);
    int t, x, y, k;
    FOR(i, 1, m+1){
        cin >> t;
        if (t == 1){
            cin >> x >> y >> k;
            oft[i] = x - y;
            upd(y, y+k, i);
        }else{
            cin >> y;
            int h = query(y);
            if (h){
                cout << a[y + oft[h]] << "\n";
            }else{
                cout << b[y] << "\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
