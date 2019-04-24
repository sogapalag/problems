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

const int N = 1000000+6;
int n;
char a[N];

struct node {
    int bk; // () = 1
    int b; //bra undo
    int k; //ket
};

void comp(node & res, node & lef, node & rig){
    int tmp = min(lef.b, rig.k);
    res.bk = lef.bk + rig.bk + tmp;
    res.b = lef.b + rig.b - tmp;
    res.k = lef.k + rig.k - tmp;
    return;
}

node tr[2 * N];

void init(){
    F0R(i, n){
        if (a[i] == '('){
            tr[i+n] = {0, 1, 0};
        }else{
            tr[i+n] = {0, 0, 1};
        }
    }
}

void build(){
    FORd(i, 1, n){
        comp(tr[i], tr[i<<1], tr[i<<1|1]);
    }
}
int query(int l, int r){
    node resl = {0, 0, 0};
    node resr = {0, 0, 0};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l & 1)
            comp(resl, resl, tr[l++]);
        if (r & 1)
            comp(resr, tr[--r], resr);
    }
    comp(resl, resl, resr);
    return resl.bk * 2;
}

void solve() {
    cin >> a;
    n = strlen(a);
    init();
    build();
    int m;
    cin >> m;
    int l, r;
    F0R(i, m){
        cin >> l >> r;
        // since [), 0-based; with cin 1-based, []
        cout << query(l-1, r) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
