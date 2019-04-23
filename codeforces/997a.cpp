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
ll x, y;
char s[300000+5];

void solve() {
    ll res = 0;
    cin >> n >> x >> y;
    cin >> s;
    int cnt = 0;
    char c = s[0];
    F0R(i, n){
        if (s[i] != c){
            cnt += 1;
            c = s[i];
        }
    }
    ll z = min(x, y);
    if (s[0] == '0'){
        res = (cnt/2) * z + y;
    }else if (cnt){
        res = ((cnt-1)/2) * z + y;
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
