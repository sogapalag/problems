#include <bits/stdc++.h>

using namespace std;

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

struct Ray {
    int x, y, tl, tr;
    Ray() {}
    Ray(int _x, int _y, int _tl, int _tr) : x(_x), y(_y), tl(_tl), tr(_tr) {}
    bool operator<(const Ray& _oth) const {
        return x < _oth.x;
    }
};

const int INF = 2e8 + 100; 

// 3. + 6. : https://codeforces.com/blog/entry/59650
// O(n log n)
// note for simple version 3. i.e. store exist all time. => rays exist all time
//   sort ray, query by x
//   then two-pointer maintain pref max, since we wanna max y = y0 +/- (x-x0),  by k = 1/-1 ray
// for time, use two segtree, put ray, query into suitable interval.
//   then we can consider the contribution, since now rays exist all in this time-interval.
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<tuple<int,int,int>>> stores(m);
    for (int _ = 0; _ < n; _++) {
        int x, tp, l, r;
        cin >> x >> tp >> l >> r;
        stores[--tp].emplace_back(x*2, l, r);
    }
    vector<pair<int, int>> qs(q);
    vector<int> ts;
    for (int _ = 0; _ < q; _++) {
        int x, t;
        cin >> x >> t;
        qs[_] = {x*2,t};
        ts.push_back(t);
    }
    ts.push_back(0);
    sort(ts.begin(), ts.end());
    ts.erase(unique(ts.begin(), ts.end()), ts.end());
    const int T = ts.size();
    auto norm = [&](int t){
        return lower_bound(ts.begin(), ts.end(), t) - ts.begin();
    };

    vector<Ray> rays;
    // for each type simulate produced rays
    for (auto& a: stores) {
        vector<tuple<int,int,int>> evs;
        for (auto& _: a) {
            int x,l,r;
            tie(x,l,r) = _;
            l = norm(l);
            r = norm(r+1);
            if (l==r) continue;
            evs.emplace_back(l, 1, x);
            evs.emplace_back(r, -1, x);
        }
        sort(evs.begin(), evs.end());
        // store pos
        multiset<int> s;
        s.insert(-5*INF); s.insert(5*INF);
        // mid(ray origin) start time
        map<int,vector<pair<int,int>>> start;
        start[0].emplace_back(5*INF, 0);

        auto push = [&](int x0, int x1, int t){
            start[(x0+x1)/2].emplace_back((x1-x0)/2, t);
        };
        auto pop = [&](int x0, int x1, int t){
            int x = (x0+x1)/2;
            auto& v = start[x];
            int y, t0;
            tie(y, t0) = v.back(); v.pop_back();
            assert(y == (x1-x0)/2);
            if (t0 == t) return;
            rays.emplace_back(x, y, t0, t);
        };

        for (auto& _: evs) {
            int t,op,x;
            tie(t,op,x) = _;
            // del a store
            if (op < 0) {
                auto it = s.find(x);
                auto lt = it, rt = it;
                --lt; ++rt;
                pop(*lt, x, t);
                pop(x, *rt, t);
                push(*lt, *rt, t);
                s.erase(it);
            } else {
                auto rt = s.lower_bound(x);
                auto lt = rt; --lt;
                pop(*lt, *rt, t);
                push(*lt, x, t);
                push(x, *rt, t);
                s.insert(x);
            }
        }
        // remain still open
        for (auto& _: start) {
            int x = _.first;
            auto& v = _.second;
            while (v.size()) {
                int y,t;
                tie(y,t) = v.back(); v.pop_back();
                if (t == T) continue;
                rays.emplace_back(x, y, t, T);
            }
        }
    }
    //for (auto& r: rays) {
    //    dbg(r.x,r.y,r.tl,r.tr);
    //}

    int N = 1;
    while (N < T) N *= 2;
    // cover seg
    vector<vector<pair<int,int>>> seg(N * 2);
    auto update = [&](int x, int y, int l, int r){
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) seg[l++].emplace_back(x, y);
            if (r&1) seg[--r].emplace_back(x, y);
        }
    };
    {
        vector<int> id(rays.size());
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return rays[u] < rays[v];
        });
        for (int i:id) update(rays[i].x, rays[i].y, rays[i].tl, rays[i].tr);
    }
    // query-seg
    vector<vector<pair<int,int>>> qseg(N * 2);
    auto qupdate = [&](int x, int i, int t){
        t = norm(t);
        for (qseg[t += N].emplace_back(x, i); t >>= 1;) {
            qseg[t].emplace_back(x, i);
        }
    };
    {
        vector<int> id(q);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return qs[u].first < qs[v].first;
        });
        for (int i:id) qupdate(qs[i].first, i, qs[i].second);
    }

    vector<int> res(q);
    for (int _ = 1; _ < 2*N; _++) {
        auto& a = seg[_];
        auto& b = qseg[_];
        if (a.empty() || b.empty()) continue;
        int n = a.size(), m = b.size();
#define x first
#define y second
        for (int l = 0, r = 0, mx = -5*INF; r < m; r++) {
            while (l < n && a[l].x <= b[r].x) {
                mx = max(mx, a[l].x + a[l].y);
                l++;
            }
            int i = b[r].y;
            res[i] = max(res[i], mx - b[r].x);
        }
        for (int l = n-1, r = m-1, mx = -5*INF; r >= 0; r--) {
            while (l >= 0 && a[l].x >= b[r].x) {
                mx = max(mx, -a[l].x + a[l].y);
                l--;
            }
            int i = b[r].y;
            res[i] = max(res[i], mx + b[r].x);
        }
    }
    for (auto& x: res) {
        x = x > INF ? -1 : x/2;
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
