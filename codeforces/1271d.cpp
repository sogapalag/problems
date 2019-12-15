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

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    vector<vector<int>> g(n);
    vector<int> mx(n);
    iota(mx.begin(), mx.end(), 0);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        mx[y] = max(mx[y], x);
        //g[x].emplace_back(y);
    }
    for (int i = 0; i < n; i++) {
        g[mx[i]].push_back(i);
    }

    vector<int> L(n); // lower bound when attack i
    L[n-1] = a[n-1];
    for (int i = n-2; i >= 0; i--) {
        L[i] = max(a[i], L[i+1]-b[i]);
    }
    if (L[0] > k) {
        cout << -1; return;
    }

    vector<int> fre(n);
    fre[0] = k - L[0];
    k = L[0] + b[0];
    for (int i = 1; i < n; i++) {
        fre[i-1] += k - L[i]; // i-1. just stand at i-1, has such free
        k = L[i] + b[i];
    }
    fre[n-1] += k;
dbg(L, fre);
    vector<bool> del(n);
    vector<bool> oready_in(n); // redundent with mx
    int res = 0;
    priority_queue<pair<int,int>> pq;
    for (int i = n-1; i >= 0; i--) {
        //pq.push({c[i], i});
        for (int v: g[i]) if(!del[v] && !oready_in[v]) {
            pq.push({c[v], v});
            oready_in[v] = true;
        }

        while (fre[i]>0 && !pq.empty()) {
            auto p = pq.top(); pq.pop();
            res += p.first;
            del[p.second] = true;
            fre[i]--;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
