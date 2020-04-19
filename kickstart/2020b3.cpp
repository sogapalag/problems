#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const ll P = 1e9; 
using pi=pair<ll, ll> ;

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
    string s; cin >> s;
    s = "1(" + s + ")";
    int n = s.size();
    int i = 0;
    function<pair<ll,ll>()> dfs = [&](){
        if (i>=n) return pi{0,0};
        ll u=0,v=0;
        int _i=i;
        if ('0'<=s[i] && s[i]<='9') {
            ll c = s[i]-'0';
            i+=2;
            ll x,y;
            while (i<n && s[i]!=')') {
                tie(x,y) = dfs();
                u += x;
                v += y;
            }
            (u*=c) %= P;
            (v*=c) %= P;
            i++;
        } else {
            if (s[i]=='W') u--;
            if (s[i]=='E') u++;
            if (s[i]=='N') v--;
            if (s[i]=='S') v++;
            ++i;
        }
        u%=P;v%=P;
        (u+=P)%=P;
        (v+=P)%=P;
dbg(_i, i, u, v);
            return pi{u,v};
        return pi{u,v};
    };
    ll x,y;
    tie(x,y) = dfs();
    cout << x+1 << ' ' << y+1 << "\n";
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
