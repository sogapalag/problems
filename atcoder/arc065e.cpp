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
using Point = pair<ll, ll>;
#define x first
#define y second
#define lb(a,v) lower_bound(a.begin(), a.end(), v)
#define ub(a,v) upper_bound(a.begin(), a.end(), v)
#define mp make_pair

// first bfs find compo, erase point, otherwise O(Edge)
// then for p in compo, find #on square.
// final res /= 2;
void solve() {
    int n, s, t;
    cin >> n >> s >> t;
    s--; t--;
    vector<Point> a(n);
    set<Point> byX, byY;
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        int u = x+y, v = x-y;
        a[i] = {u, v};
        if (i != s) {
            byX.emplace(u,v);
            byY.emplace(v,u);
        }
    }
    const ll D = max(abs(a[s].x-a[t].x), abs(a[s].y-a[t].y));
dbg(a, D);
    // bfs
    vector<Point> compo;
    queue<Point> q;
    q.push(a[s]);
    while (!q.empty()) {
        ll x,y;
        tie(x,y) = q.front(); q.pop();
        compo.emplace_back(x, y);
        // 1 --> 2
        // ^     |
        // |     v
        // 0 <-- 3
        
        ll u,v;
        // 0->1
        auto it = byX.lower_bound({x-D, y-D});
        while (it != byX.end()) {
            tie(u,v) = *it;
            if (u != x-D || v > y+D) break;
            q.push(*it);
            byY.erase({v, u});
            it = byX.erase(it);
        }
        // 1->2 x,y (y,x)
        it = byY.lower_bound({y+D, x-D});
        while (it != byY.end()) {
            tie(v,u) = *it;
            if (v != y+D || u > x+D) break;
            q.push({u, v});
            byX.erase({u,v});
            it = byY.erase(it);
        }
        // 2<-3
        it = byX.lower_bound({x+D, y-D});
        while (it != byX.end()) {
            tie(u,v) = *it;
            if (u != x+D || v > y+D) break;
            q.push(*it);
            byY.erase({v,u});
            it = byX.erase(it);
        }
        // 0->3
        it = byY.lower_bound({y-D, x-D});
        while (it != byY.end()) {
            tie(v,u) = *it;
            if (v != y-D || u > x+D) break;
            q.push({u,v});
            byX.erase({u,v});
            it = byY.erase(it);
        }
    }
dbg(compo);
    ll res = 0;
    sort(a.begin(), a.end());
    for (auto& p: compo) {
        ll x,y;
        tie(x,y) = p;
        res += ub(a, mp(x-D,y+D)) - lb(a, mp(x-D,y-D));
        res += ub(a, mp(x+D,y+D)) - lb(a, mp(x+D,y-D));
    }
    for (auto& p: a) {
        swap(p.x,p.y);
    }
    sort(a.begin(), a.end());
    for (auto& p: compo) {
        ll x,y;
        tie(x,y) = p;
        res += lb(a, mp(y-D,x+D)) - lb(a, mp(y-D,x-D+1));
        res += lb(a, mp(y+D,x+D)) - lb(a, mp(y+D,x-D+1));
    }
    res >>= 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
