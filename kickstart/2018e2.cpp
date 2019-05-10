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
const int inf = 0x3f3f3f3f;
const int MX = 100001;
const int CF = 300005;

int n, m, p;

// dijkstra + greedy; since each bit separatly cost
void solve() {
    cin >> n >> m >> p;
    vi c(p, 0);
    F0R(_, n){
        string s; cin >> s;
        F0R(i, p)
            if (s[i] == '1')
                c[i]++;
    }
    unordered_set<string> forbid;
    F0R(_, m){
        string s; cin >> s;
        forbid.insert(s);
    }

    vpi b(p);
    vi fc(p);
    F0R(i, p)
        b[i] = {max(c[i], n-c[i]), i};
    int res = 0;
    F0R(i, p){
        res += n - b[i].f;
        fc[i] = b[i].f * 2 - n;
    }
    string S(p, '1');
    F0R(i, p){
        if (b[i].f > c[i])
            S[i] = '0';
    }
    struct STR{
        int v;
        string s;
    };
    STR ini = {res, string(S)};
    auto flip = [](char &x){
        if (x == '0')
            x = '1';
        else if (x == '1')
            x = '0';
    };
    auto comp = [](STR& x, STR& y){return x.v > y.v;};
    std::priority_queue<STR, vector<STR>, decltype(comp)> pq(comp);
    pq.push(ini);
    while (!pq.empty()){
        STR x = pq.top(); pq.pop();
        if (forbid.find(x.s) == forbid.end()){
            cout << x.v; return;
        }
        F0R(i, p){
            if (x.s[i] == S[i]){
                flip(x.s[i]);
                x.v += fc[i];
                pq.push(x);
                flip(x.s[i]);
                x.v -= fc[i];
            }
        }
    }
}

// another way dp[x] #ways, x:#complains.(at most n*p)
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    FOR(t, 1, T+1){
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
}
