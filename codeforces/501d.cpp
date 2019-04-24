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

const int N = 200000 + 5;

int n;
int perm[N];
//ord  d[0]...d[n-1], digits reversely view, i.e. 0x1x2x3.. is bigger 
int dp[N]; 
int dq[N];

// https://en.wikipedia.org/wiki/Factorial_number_system
// https://en.wikipedia.org/wiki/Lehmer_code
void solve() {
    cin >> n;
    Tree<int> set;
    int p, q;
    F0R(i, n)
        cin >> perm[i];
    F0R(i, n){
        p = perm[n-1-i];
        dp[i] = set.order_of_key(p);
        set.insert(p);
    }
    set.clear();
    F0R(i, n)
        cin >> perm[i];
    F0R(i, n){
        q = perm[n-1-i];
        dq[i] = set.order_of_key(q);
        set.insert(q);
    }
    // sum
    int cry = 0;
    F0R(i, n){
        int tmp = dp[i] + dq[i] + cry;
        dp[i] = tmp % (i+1);
        cry = tmp / (i+1);
    }
    // set{0,..,n-1}, Lehmer code exatcly k elems less, 
    //                 happens current k-th smallest
    F0Rd(i, n){
        p = *set.find_by_order(dp[i]);
        cout << p << ' ';
        set.erase(p);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
