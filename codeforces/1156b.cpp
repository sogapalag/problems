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

int cnt[26];
        
void solve() {
    char s[111];
    cin >> s;
    int n = strlen(s);
    memset(cnt, 0, sizeof cnt);
    F0R(i, n){
        int t = s[i] - 'a';
        cnt[t]++;
    }
    string s0 = "", s1 = "";
    F0R(i, 26){
        if (i&1 && cnt[i])
            s1 += string(cnt[i], 'a'+i);
        if (!(i&1) && cnt[i])
            s0 += string(cnt[i], 'a'+i);
    }
    if (s0.empty()){
        cout << s1 << '\n'; return;
    }
    if (s1.empty()){
        cout << s0 << '\n'; return;
    }
    int dif = *s0.begin() - *s1.rbegin();
    if (abs(dif) != 1){
        cout << s1 << s0 << '\n'; return;
    }
    dif = *s1.begin() - *s0.rbegin();
    if (abs(dif) != 1){
        cout << s0 << s1 << '\n'; return;
    }
    cout << "No answer\n";
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int T; cin >> T;
    while (T--)
        solve();
    //cout << endl;
}
