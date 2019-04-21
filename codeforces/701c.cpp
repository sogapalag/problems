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
int c[55];
char s[100000 + 5];


void solve() {
    int res = 1<<30;
    memset(c, 0, sizeof c);
    memset(s, 0, sizeof s);
    cin >> n;
    cin >> (s+1);
    unordered_set<char> st;
    FOR(i, 1, n+1){
        st.insert(s[i]);
    }
    int sz_st = sz(st);
    unordered_map<char, int> ct;
    int i = 1, j = 1;
    while (j <= n){
        while (sz(ct) < sz_st && j<= n){
            ct[s[j]] += 1;
            j += 1;
        }
        while (sz(ct) == sz_st){
            ct[s[i]] -= 1;
            if (!ct[s[i]]){
                ct.erase(s[i]);
            }
            i += 1;
        }
        int d = j - i + 1;
        res = min(res, d);
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
