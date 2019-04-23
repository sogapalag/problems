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

const int N = 1000000+5;
int n;
int a[N];
int l[N];
int r[N];
int tr[2 * N];

void upd(int p, int val){
    for (tr[p += n] += val; p > 1; p >>= 1){
        tr[p>>1] = tr[p] + tr[p^1];
    }
}
// query [l, r)
int query(int l, int r){
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            res += tr[l++];
        if (r & 1)
            res += tr[--r];
    }
    return res;
}

void solve() {
    cin >> n;
    FOR(i, 1, n+1){
        cin >> a[i];
    }
    unordered_map<int, int> map;
    FOR(i, 1, n+1){
        map[a[i]] += 1;
        l[i] = map[a[i]] - 1; // for 0-based
    }
    map.clear();
    FORd(i, 1, n+1){
        map[a[i]] += 1;
        r[i] = map[a[i]] - 1; // for 0-based
    }

    memset(tr, 0, sizeof tr);
    ll res = 0;
    FOR(i, 1, n+1){
        res += i-1 - query(0, r[i]+1);
        upd(l[i], 1);
    }
    cout << res;
}

int main() {
    solve();
    cout << endl;
}
