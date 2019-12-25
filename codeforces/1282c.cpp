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
struct Node {
    int t, h;
    Node() {}
    Node(int _t, int _h) : t(_t), h(_h) {}
    bool operator<(const Node& _oth) const {
        return t<_oth.t;
    }
};

void solve() {
    int n, T, A, B;
    cin >> n >> T >> A >> B;
    vector<Node> a(n);
    int E=0, H=0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        H += x;
        E += x^1;
        a[i].h = x;
    }
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        a[i].t = t;
    }
    sort(a.begin(), a.end());
    int res = 0;
    int i = -1;
    int e=0,h=0;
    while (i < n) {
        int t;
        if (i<0) {
            t = 0; i=0;
        }else t = a[i].t;
        while (i<n && a[i].t==t) {
            e += a[i].h^1;
            h += a[i].h;
            i++;
        }
        int now = i<n?a[i].t-1:T;
        ll must = 1ll*e*A + 1ll*h*B;
        if (now < must) continue;
        int tmp = e+h;
        ll rem = now-must;
dbg(now, must);
        ll x = min(rem/A, (ll)E-e);
        tmp += x; rem -= x*A;
dbg(x, tmp);
        x = min(rem/B, (ll)H-h);
        tmp += x;
dbg(x, tmp);
        res = max(res, tmp);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
