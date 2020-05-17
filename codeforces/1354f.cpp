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
#define dbg(args...) 2020
#endif

const int N = 80; 
int dp[N][N];

// note optimal-form: put m-1 into set, use n-m to buff them +y*(m-1), finally add 1 into set.
// and note the set join order by y, since +y*j
void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u].second < a[v].second;
    });
    memset(dp, 0xc0, sizeof dp); // 0 WA, +y*j has val. need to assign NINF.
    dp[0][0] = 0;
    for (int _ = 0; _ < n; _++) {
        int i = id[_];
        int x,y;
        tie(x,y) = a[i];
        for (int j = 0; j <= m; j++) {
            dp[_+1][j] = dp[_][j] + y*(m-1);
        }
        for (int j = 0; j < m; j++) {
            dp[_+1][j+1] = max(dp[_+1][j+1], dp[_][j] + x + y*j);
        }
    }
    //cerr << dp[n][m] << endl;
    vector<int> stay, buff;
    for (int _ = n-1, j = m; _ >= 0; _--) {
        int i = id[_];
        int x,y;
        tie(x,y) = a[i];
        if (j>0 && dp[_+1][j] == dp[_][j-1] + x + y*(j-1)) {
            stay.push_back(i); --j;
        } else {
            buff.push_back(i);
        }
        //if (dp[_+1][j] == dp[_][j] + y*(m-1)) {
        //    buff.push_back(i);
        //} else {
        //    stay.push_back(i);
        //    --j;
        //}
    }
    reverse(stay.begin(), stay.end());
    reverse(buff.begin(), buff.end());
dbg(stay, buff);
    cout << 2*n-m << '\n';
    for (int i = 0; i < m-1; i++) {
        cout << stay[i]+1 << ' ';
    }
    for (int i:buff) {
        cout << (i+1) << ' ';
        cout << -(i+1)<< ' ';
    }
    cout << stay.back()+1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
