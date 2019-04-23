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

int n, k;
int a[5555];

// add some counter may fix, but try other easy one.
void wrong_solve() {
    unordered_map<int, int> map;
    cin >> n >> k;
    FOR(i, 1, n+1){
        cin >> a[i];
        map[a[i]] += 1;
    }
    if  (n < k){
        cout << "NO";
        return;
    }
    for (auto &p: map){
        if (p.s > k){
            cout << "NO";
            return;
        }
    }
    cout << "YES" << endl;
    int cnt = 0;
    unordered_map<int, int> co;
    FOR(i, 1, n+1){
        if (co.count(a[i])){
            co[a[i]] = (1 + co[a[i]]) % k;
            cout << co[a[i]] + 1 << ' ';
        }else{
            co[a[i]] = cnt;
            cnt = (1 + cnt) % k;
            cout << co[a[i]] + 1 << ' ';
        }
    }
}

void solve(){
    cin >> n >> k;
    vpi a(n);
    unordered_map<int, int> map;
    F0R(i, n){
        cin >> a[i].f;
        map[a[i].f] += 1;
        a[i].s = i;
    }
    if  (n < k){
        cout << "NO";
        return;
    }
    for (auto &p: map){
        if (p.s > k){
            cout << "NO";
            return;
        }
    }
    sort(all(a));
    vi res(n);
    F0R(i, n){
        res[a[i].s] = (i%k) + 1;
    }
    cout << "YES" << endl;
    F0R(i, n){
        cout << res[i] << ' ';
    }
}

int main() {
    solve();
    cout << endl;
}
