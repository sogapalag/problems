#include <bits/stdc++.h>

using namespace std;
#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;

const int N = 51; 
ll dp[N][N];
ll f[N], g[N];
// f[n]: total derangement of [n], pi!=i, and all in one cycle.
// dp[n][j]: #good-perm, s.t. first j same cycle, i.e. j...., 
// g[n]: sum of dp, i.e. #good-perm of [n]
void prep() {
    f[0]=f[1]=f[2]=1;
    for (int i = 3; i < N; i++) {
        if (f[i-1] >= INF/(i-1)) f[i] = INF;
        else f[i] = (i-1) * f[i-1];
        dbg(f[i]);
    }
    g[0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            // max is 1st
            if (f[j-1] > INF/g[i-j]) dp[i][j] = INF;
            else dp[i][j] += f[j-1] * g[i-j];
            if (dp[i][j] > INF) dp[i][j] = INF;
            // sum
            g[i] += dp[i][j];
            if (g[i] > INF) g[i] = INF;
        }
        dbg(g[i]);
    }
}
void solve() {
    int n; ll k;
    cin >> n >> k;
    if (k > g[n]) {
        cout << "-1\n"; return;
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);

    vector<bool> trk(n);
    auto sw = [&](int i, int x){
        trk[x] = true;
        int j = a[x];
        //assert(p[i] != p[j]);
        swap(p[i], p[j]);
        a[p[i]] = i;
        a[p[j]] = j;
    };
    for (int i = 0; i < n;) {
        int j = 1;
        while (k > dp[n-i][j]) {
            k -= dp[n-i][j];
            j++;
        }
        //cerr<<i<<endl;
        sw(i, i+j-1); // max be first
        int _i = i;
        i++; j--;
        while (j > 1) {
            int x = _i;
            // pick smallest
            while (true) {
                while (trk[x] || a[x]==i) {// hold derangement
                    x++;
                }
                if (k > dp[n-i][j]) {
                    x++; k -= dp[n-i][j];
                }else break;
            }
            //while (!trk[x] && (a[x]!=i?1:x+=1,0) && k > dp[n-i][j]) {
            //    x++; k -= dp[n-i][j];
            //}
            sw(i, x);
            i++; j--;
        }
        if (j>0) i++,j--;
        // end of fill j..., fill same sub problem n-j
    }
    for (int x: p) {
        cout << x+1 << ' ';
    }cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
