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
#define dbg(args...) 2020
#endif

// dominated (a,a+k) >= (a',b'),   =>   (a,a+k) >= #by(a',a'+k), i.e. transist holds.
//   the trick part is handle one might not dominated itself.
void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }

    auto iep = [&](int k){
        ll res = 0;
        vector<int> L(n), R(n);
        vector<int> stk;
        for (int i = 0; i < n; i++) {
            if (b[i] > a[i] + k) {
                L[i] = i + 1;
                goto nxt;
            }
            while (!stk.empty()) {
                int l = stk.back();
                if (a[l] >= a[i]) break;
                if (b[l] > a[i] + k) break;
                stk.pop_back();
            }
            L[i] = stk.empty() ? 0 : stk.back()+1;
nxt:;
            stk.push_back(i);
        }
        stk.clear();
        for (int i = n-1; i >= 0; i--) {
            if (b[i] > a[i] + k) {
                R[i] = i-1;
                goto nnxt;
            }
            while (!stk.empty()) {
                int r = stk.back();
                if (a[r] > a[i]) break;
                if (b[r] > a[i] + k) break;
                stk.pop_back();
            }
            R[i] = stk.empty() ? n-1 : stk.back()-1;
nnxt:;
            stk.push_back(i);
            if (L[i] <= i && i <= R[i]) {
                res += (i-L[i]+1) * 1ll * (R[i]-i+1);
            }
        }
dbg(L,R,res);
        return res;
    };
    cout << iep(K)-iep(-K-1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
