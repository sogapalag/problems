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
char ta[111][111];
int res = 0;

void check(vpi & crt, int j){
    if (j == m){
        return;
    }
    //for (auto &p: crt){
    //    cout << p.f << ' ' << p.s << ',';
    //}
    //cout << endl;
    vpi nex;
    bool valid = true;
    for (auto &p: crt){
        char c = ta[p.f][j];
        int l = p.f;
        FOR(i, p.f, p.s){
            if (c > ta[i][j]){
                valid = false;
                res += 1;
                break;
            }else if (c < ta[i][j]){
                nex.pb(mp(l, i));
                l = i;
                c = ta[i][j];
            }
        }
        if (!valid){
            break;
        }
        nex.pb(mp(l, p.s));
    }
    if (valid){
        check(nex, j+1);
    }else{
        check(crt, j+1);
    }
}

void solve() {
    cin >> n >> m;
    F0R(i, n){
        cin >> ta[i];
    }
    vpi crt;
    crt.pb(mp(0, n));
    check(crt, 0);
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
