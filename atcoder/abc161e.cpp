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

void solve() {
    int n,k,c;
    cin >> n >> k >> c;
    string s; cin >> s;
    vector<int> L(n + 1), R(n + 1);
    vector<int> sum(n + 1);
    // prep greedy left/right boarder
    int cnt = 0;
    for (int i = 0; i < n;) {
        if (s[i]=='o') {
            i += c+1;
            L[++cnt] = i;
        }else i++;
    }
    if (cnt != k) {
        cout << "\n"; return;
    }
    R[0] = n-1+c;
    for (int i = n-1, cnt = 0; i >= 0;) {
        if (s[i]=='o') {
            R[++cnt] = i-1;
            i -= c+1;
        } else i--;
    }
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + (s[i]=='o');
    }
    vector<int> res;
    for (int i = 1; i <= k; i++) {
        // check i-th element #candidates
        int l = L[i-1];
        int r = R[k-i];
dbg(i, l, r);
        r -= c;
        if (l > r) continue;
        if (sum[r+1] - sum[l] == 1) {
            for (int x = l; x <= r; x++) {
                if (s[x]=='o') res.push_back(x);
            }
        }
    }
    for (auto& x: res) {
        cout << x+1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
