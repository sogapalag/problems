#include <bits/stdc++.h>

using namespace std;
template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
template <typename T>
struct RASQ {
    int n;
    Fenwick<T> diff;

    RASQ(int _n) : n(_n), diff(n) {}
    // 1-based, [l..r)
    inline void add(int l, int r, T val) {
        diff.add(l, val);
        diff.add(r, -val);
    }
    inline T query(int p) {
        return diff.query(p);
    }
};
template <typename T>
struct RARQ {
    int n;
    RASQ<T> a;
    Fenwick<T> lack;

    RARQ(int _n) : n(_n), a(n), lack(n) {}

    // 0-based [l..r)
    inline void add(int l, int r, T val) {
        a.add(l+1, r+1, val);
        lack.add(l+1, val * l);
        lack.add(r+1, val * (-r));
    }
    // 0-based [0..p)
    inline T query(int p) {
        return a.query(p)*p - lack.query(p);
    }
    // 0-based [l..r)
    inline T query(int l, int r) {
        return query(r) - query(l);
    }
};
#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
string to_string(tuple<int,int,int,int>& a) {
    return "("+to_string(get<0>(a))+
           ","+to_string(get<1>(a))+
           ","+to_string(get<2>(a))+
           ","+to_string(get<3>(a))+")";
}
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
// a segment(1-run), [l..r), exist time range [tl..tr)
// contribute to query only when l<=x && y<=r. recall partial_ord_3d. or cdq divi
// another method, note each modify, a 2d-rect range-add. so can maintain by tree2d for online. omit
void solve() {
    int n,q;
    cin >> n >> q;
    string s; cin >> s;
    map<int,pair<int,int>> seg; // 1-run
    for (int l = 0; l < n;) {
        if (s[l] == '1') {
            int r = l;
            while (r < n && s[r] == '1') {
                r++;
            }
            seg[l] = {r, 0};
            l = r;
        } else l++;
    }
    vector<tuple<int,int,int,int>> evs;
    //vector<tuple<int,int,int>> qrs;
#define fi first
#define se second
    int qcnt = 0;
    map<int,int> res; //.. 0 may not exist..
    for (int t = 1; t <= q; t++) {
        string op; cin >> op;
        if (op[0] == 't') {
            int i; cin >> i; i--;
            s[i] ^= 1;
            if (s[i] == '1') {
                int l = i;
                // remove left
                if (i && s[i-1]=='1') {
                    auto it = --seg.lower_bound(i);
                    evs.emplace_back(l = it->fi, it->se.fi, it->se.se, t);
                    seg.erase(it);
                }
                int r = i+1;
                // remove right
                if (r<n && s[r]=='1') {
                    auto it = seg.lower_bound(i);
                    evs.emplace_back(it->fi, r = it->se.fi, it->se.se, t);
                    seg.erase(it);
                }
                // merge
                seg[l] = {r, t};
            } else {
                auto it = --seg.upper_bound(i);
                int l = it->fi;
                int r, tl;
                tie(r, tl) = it->se;
                evs.emplace_back(l, r, tl, t);
                // left
                if (l < i) {
                    it->se = {i, t};
                } else seg.erase(it);
                // right
                if (i+1 < r) {
                    seg[i+1] = {r, t};
                }
            }
        } else {
            qcnt++;
            int x,y;
            cin >> x >> y;
            x--;y--;
            evs.emplace_back(x, y, t, -1);
            res[t] = 0;
        }
    }
    for (auto& _: seg) {
        int l = _.fi;
        int r, tl;
        tie(r, tl) = _.se;
        evs.emplace_back(l,r,tl,q);
    }
if(0)for (auto& x: evs) {
    dbg(x);
}
//dbg(qcnt);
//dbg(evs.size());
    sort(evs.begin(), evs.end(), [&](auto& u, auto& v){
        return get<0>(u) < get<0>(v) || (get<0>(u)==get<0>(v) && get<3>(u) > get<3>(v)); // ensure query later
    });// get<3>(v)==-1 would infini-loop...
    auto comp = [](auto& u, auto& v){
        return get<1>(u) < get<1>(v);
    };
    
    RARQ<int64_t> ra(q + 5);
    auto& a = evs;
    function<void(int,int)> divi = [&](int l, int r){
        if (r-l <= 1) return;
        int m = (l+r)/2;
        divi(l,m); divi(m,r);
        int i = m-1;
        for (int j = r-1; j >= m; j--) {
            while (i >= l && get<1>(a[i]) >= get<1>(a[j])) {
                int tl = get<2>(a[i]);
                int tr = get<3>(a[i--]);
                if (tr == -1) continue;
                ra.add(tl, tr, 1);
            }
            int tl = get<2>(a[j]);
            int tr = get<3>(a[j]);
            if (tr == -1) {
                res[tl] += ra.query(tl); // +=..
            }
        }
        // recover
        while (++i < m) {
            int tl = get<2>(a[i]);
            int tr = get<3>(a[i]);
            if (tr == -1) continue;
            ra.add(tl, tr, -1);
        }
        inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r, comp);
    };
    divi(0, a.size());
    for (auto& _: res) {
        cout << _.se << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
