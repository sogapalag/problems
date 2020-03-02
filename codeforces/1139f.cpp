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
enum {
    LDIAG, // /
    RDIAG, // \ .
    QUERY,
};
struct Event {
    int x, y, z;
    int type;
    Event() {}
    Event(int _x, int _y, int _z, int _type) : x(_x), y(_y), z(_z), type(_type) {}
    bool operator<(const Event& _oth) const {
        return x < _oth.x || (x == _oth.x && type < _oth.type );
    }
};

//     /\.
//    /  \.
//   /____\.
//   note a (p,s,b) contrbute to a triangle, => split two diags
//    i.e. when =p, trigger 
//   L:    /         R:  \.
//     000/1111       0000\111
//     one can see L-R = 1 iff the point in the triangle.
//     then when =s, release
//
// there also another overkill method, i.e. sparse_counter. d&c, {s,p,inc} as time. triangle is indeed square when rotate 45, as long as we reset it when =s.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> p(n), s(n), b(n), inc(m), pref(m);
    for (auto& x:p) cin >> x;
    for (auto& x:s) cin >> x;
    for (auto& x:b) cin >> x;
    for (auto& x:inc) cin >> x;
    for (auto& x:pref) cin >> x;
    vector<int> Zs;
    for (int i = 0; i < n; i++) {
        ++s[i];
        Zs.push_back(p[i] + b[i]);
        Zs.push_back(b[i] + 1 - p[i]);
    }
    for (int i = 0; i < m; i++) {
        Zs.push_back(inc[i] + pref[i]);
        Zs.push_back(pref[i] + 1 - inc[i]);
    }
    sort(Zs.begin(), Zs.end());
    Zs.erase(unique(Zs.begin(), Zs.end()), Zs.end());

    vector<Event> evs;
    for (int i = 0; i < n; i++) {
        int y = p[i] + b[i];
        y = lower_bound(Zs.begin(), Zs.end(), y) - Zs.begin();
        y++;
        evs.emplace_back(p[i], y, 1, LDIAG);
        evs.emplace_back(s[i], y, -1, LDIAG);
        y = b[i] + 1 - p[i];
        y = lower_bound(Zs.begin(), Zs.end(), y) - Zs.begin();
        y++;
        evs.emplace_back(p[i], y, 1, RDIAG);
        evs.emplace_back(s[i], y, -1, RDIAG);
    }
    for (int i = 0; i < m; i++) {
        evs.emplace_back(inc[i], pref[i], i, QUERY);
    }
    sort(evs.begin(), evs.end());

    Fenwick<int> L(Zs.size()), R(Zs.size());
    vector<int> res(m);
    for (auto& e: evs) {
        if (e.type == LDIAG) {
            L.add(e.y, e.z);
        } else if (e.type == RDIAG) {
            R.add(e.y, e.z);
        } else {
            int y = e.x+e.y, i = e.z;
            y = lower_bound(Zs.begin(), Zs.end(), y) - Zs.begin();
            y++;
            res[i] += L.query(y);
            y = e.y+1-e.x;
            y = lower_bound(Zs.begin(), Zs.end(), y) - Zs.begin();
            y++; y--; // here --, e.g. at(p,b) wanna 1-0=1, so exclude boarder of R
            res[i] -= R.query(y);
        }
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
