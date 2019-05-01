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

#define __seg_p (int _l, int _r, int val, int p=1, int l=0, int r=N)
#define __seg_out if (_r <= l || r <= _l)
#define __seg_in if (_l <= l && r <= _r)
#define __seg_one if (l+1 == r)
#define __seg_calc int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
#define __seg_l (_l, _r, val, pl, l, m)
#define __seg_r (_l, _r, val, pr, m, r)

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100005;
const int CF = 300005;

const int N = MX;

int n, q;
int a[N], lv[N], fail[N], pre[N], fen[N], f3n[N];
int res[N];
struct req{
    int id, l, r;
};
req r[N];

void allset(){
    memset(lv, 0, sizeof lv);
    memset(fail, 0, sizeof fail);
    memset(pre, 0, sizeof pre);
    memset(fen, 0, sizeof fen);
    memset(f3n, 0, sizeof f3n);
}

// every update, crt idx +1, previous val idx -1, thus,. sum is #type
// record fail[i] for i, i.e. if include fail[i], not an equal-diff
// use another BIT store, +1 for idx, -1 for fail idx.
// then finally need another modif iff s==f
// for comment the not nomral way BIT. watch out the BIT graph, to see
//  -= lbit chain is like 
//  ---------------
//                |----
//                    |--<
// += lbit chain is like
//            |---.
//          --|
//       ---|
//      >|
// since each update, in right's order, it's totally valid.
// well since may not easily imagine, try normal way out.
void solve() {
    allset();
    cin >> n;
    FOR(i, 1, n+1){
        cin >> a[i];
        pre[i] = lv[a[i]];
        lv[a[i]] = i;
        if (i + pre[pre[i]] == 2 * pre[i])
            fail[i] = fail[pre[i]];
        else
            fail[i] = pre[pre[i]];
    }
    cin >> q;
    FOR(i, 1, q+1){
        r[i].id = i;
        cin >> r[i].l >> r[i].r;
    }
    sort(r+1, r+q+1, [](req & x, req & y) {return x.r < y.r;});
    int p, k=1;
 //   FOR(i, 1, n+1){
 //       for(p=i; p; p -= lbit(p))
 //           fen[p]++;
 //       for(p=pre[i]; p; p -= lbit(p))
 //           fen[p]--;
 //       for(p=fail[i]; p; p -= lbit(p))
 //           f3n[p]++;
 //       for(p=fail[pre[i]]; p; p -= lbit(p))
 //           f3n[p]--;
 //       while (r[k].r == i && k <= q){
 // reverse order          int s=0, f=0;
 //           for(p=r[k].l; p<=i; p += lbit(p))
 //               s += fen[p];
 //           for(p=r[k].l; p<=i; p += lbit(p))
 //               f += f3n[p];
 //           res[r[k].id] = s + (s==f);
 //           k++;
 //       }
 //   }
    FOR(i, 1, n+1){
        for(p= i;       p<=N; p += lbit(p))
            fen[p]++;
        for(p= pre[i]; p && p<=N; p += lbit(p))
            fen[p]--;
        for(p= fail[i]; p && p<=N; p += lbit(p))
            f3n[p]++;
        for(p= fail[pre[i]]; p && p<=N; p += lbit(p))
            f3n[p]--;
        while (r[k].r == i && k <= q){
            int s=0, f=0, t=0;
            for(p=i; p>0; p -= lbit(p))
                s += fen[p];
            for(p=r[k].l-1; p>0; p -= lbit(p))
                t += fen[p];
            s -= t;  t=0;
            for(p=i; p>0; p -= lbit(p))
                f += f3n[p];
            for(p=r[k].l-1; p>0; p -= lbit(p))
                t += f3n[p];
            f -= t;
            res[r[k].id] = s + (s==f);
            k++;
        }
    }
    FOR(i, 1, q+1)
        cout << res[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    //cout << endl;
}
