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
const int N = 80005; 
vector<int> g[N<<1];
char tp[N<<1];

// first note best = C*R
// then observe for serial, C = min(C_i), for parallel sqrtC = sum sqrtC_i. recall lagrange
// for any used leaf, set sqC*R
void solve() {
    ll R; string s;
    cin >> R;
    getline(cin, s);
    vector<int> stk; int cnt = 0;
    // trim contruct
    for (char x: s) if(x!=' '){
        if (x=='(') {
            stk.emplace_back(cnt++);
        } else if (x==')') {
            int v = stk.back(); stk.pop_back();
            if (!stk.empty()) g[stk.back()].push_back(v);
        } else if (x=='*') {
            tp[cnt] = '*';
            if (!stk.empty()) g[stk.back()].push_back(cnt);
            cnt++;
        } else {
            assert(x=='S'||x=='P');
            tp[stk.back()] = x;
        }
    }
    
    vector<ll> sqc(cnt);
    vector<int> mi_id(cnt);
    function<void(int)> dfs = [&](int u){
        if (tp[u]=='*') {
            sqc[u] = 1ll;
        } else if (tp[u]=='S') {
            ll mi = 1ll<<60;
            for (int v: g[u]) {
                dfs(v);
                if (sqc[v] < mi) {
                    mi = sqc[v];
                    mi_id[u] = v;
                }
            }
            sqc[u] = mi;
        } else {
            sqc[u] = 0;
            for (int v: g[u]) {
                dfs(v);
                sqc[u] += sqc[v];
            }
        }
    };
    vector<bool> use(cnt); use[0] = true;
    function<void(int)> assign = [&](int u){
        if (tp[u]=='S') {
            int v = mi_id[u];
            use[v] = true;
            assign(v);
        } else if (tp[u]=='P'){
            for (int v: g[u]) {
                use[v] = true;
                assign(v);
            }
        }
    };
    dfs(0);
    assign(0);
dbg(sqc, mi_id);
    cout << "REVOLTING";
    for (int i = 0; i < cnt; i++) {
        if (tp[i]=='*') {
            ll r = sqc[0]*R*use[i];
            cout << ' '<<r;
        }
    }cout << '\n';

    for (int i = 0; i < cnt; i++) {
        g[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
