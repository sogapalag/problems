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

const int N = 100000 + 5;

int n, t;

struct node {
    int a, e, g; //alive, eat, gcd
};

node tr[2 * N];

// be careful void (res, res, rig) function. read after modify. 
node comp(node & lef, node & rig){
    if (!lef.g){
        return rig;
    }
    node res;
    int tcd = __gcd(lef.g, rig.g);
    res.a = lef.a + rig.a;
    res.e = lef.e + rig.e;
    res.g = tcd;
    if (tcd != lef.g){
        res.a -= lef.a;
        res.e += lef.a;
    }
    if (tcd != rig.g){
        res.a -= rig.a;
        res.e += rig.a;
    }
    return res;
}

void build(){
    FORd(i, 1, n){
        tr[i] = comp(tr[i<<1], tr[i<<1|1]);
        //cout << i << ',' << tr[i].a << '.' << tr[i].e << '.' << tr[i].g <<endl;
    }
}
int query(int l, int r){
    node res = {0, 0, 0};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            res = comp(res, tr[l++]);
        if (r & 1)
            res = comp(res, tr[--r]);
    }
    return res.e;
}

void solve() {
    cin >> n;
    int s;
    F0R(i, n){
        cin >> s;
        tr[i+n] = {1, 0, s};
    }
    build();
    int t, l, r;
    cin >> t;
    F0R(i, t){
        cin >> l >> r;
        cout << query(l-1, r) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
