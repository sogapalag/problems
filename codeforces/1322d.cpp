#include <bits/stdc++.h>

using namespace std;

const int N = 2048; 
int dp[2*N][N];

#define LOCAL
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

// in reverse-order, recall game 2048, 
// dp[level][cnt], cnt = #level
// each time, a[i]=x, we only need to care [x][..], 
// then for larger level update, [y][./2], each time half-sized.
// total asym O(n^2)
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> b(n);
    for (auto& x: b) {
        cin >> x;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int> prof(n + m + 1 + N*2);
    for (int i = 1; i <= n + m; i++) {
        cin >> prof[i];
    }

    memset(dp, 0xc0, sizeof dp);
    for (int i = 1; i <= n + m; i++) {
        dp[i][0] = 0;
    }
    auto maxi = [](int& x, int y){
        if (x < y) x = y;
    };
    const int L = 20; 
    for (int _ = 0; _ < n; _++) {
        int x = a[_];
        int c = b[_];
        //for (int i = 0; i <= _; i++) {
        for (int i = _; i >= 0; i--) {
            maxi(dp[x][i + 1], dp[x][i] - c + prof[x]);
        }
//dbg(dp[1][1]);
        int k = _ + 1;
        for (int y = x; y < x + L; y++, k/=2) {
            for (int i = 0; i <= k; i++) {
                maxi(dp[y + 1][i / 2], dp[y][i] + prof[y+1] * (i/2)); // i...
            }
            //dbg(y+1, dp[y+1][0]);
        }
        for (int y = x+L; y < n+m; y++) {
            maxi(dp[y+1][0], dp[y][0]);
            //dbg(y+1, dp[y+1][0]);
        }
    }
    cout << dp[n+m][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
