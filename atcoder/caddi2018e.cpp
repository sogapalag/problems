#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

const int L = 16;
const int N = 200005; 
ll dp[L][N]; // when fixed use j on i, later is greedy,

int log4(ll x, ll y) {
    if (x >= y) {
        int e = 0;
        while (x > y) {
            y <<= 2;
            e++;
        }
        return e;
    } else {
        int e = 1;
        while (x <= y) {
            x <<= 2;
            e--;
        }
        return e;
    }
}

vector<ll> calc(const vector<int>& a) {
    int n = a.size();
    for (int j = 0; j < L; j++) {
        dp[j][n-1] = j;
    }
    for (int i = n-1; i >= 1; i--) {
        int e = log4(a[i-1], a[i]);
        for (int j = 0; j < L; j++) {
            dp[j][i-1] = j;
            int k = max(j+e, 0);
            dp[j][i-1] += k<L? dp[k][i] : dp[L-1][i] + (k-L+1)*(n-i);
        }
    }
    vector<ll> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = dp[0][i] << 1;
    }
    return res;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    auto suf = calc(a);
    reverse(a.begin(), a.end());
    auto pre = calc(a);
    reverse(pre.begin(), pre.end());
dbg(suf, pre);
    ll res = min(suf[0], pre[n-1]+n);
    for (int i = 1; i < n; i++) {
        ll tmp = pre[i-1] + i + suf[i];
        res = min(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
