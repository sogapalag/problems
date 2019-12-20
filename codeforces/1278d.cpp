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

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());

    auto gg = [](){
        cout << "NO"<<endl;exit(0);
    };
    int cnt = 0;
    set<pair<int,int>> s;
    Dsu d(n);
    s.emplace(a[0].second, 0);
    dbg(a);
    for (int i = 1; i < n; i++) {
        int x,y;
        tie(x,y)=a[i];
        while (!s.empty() && s.begin()->first <= x) {
            s.erase(s.begin());
        }
        dbg(s);
        if(s.empty()) gg();
        for (auto it = s.begin(); it != s.end(); it++) {
            if (it->first > y) break;
            int j = it->second;
            if (!d.join(i,j)) gg();
            cnt++;
            if (cnt >= n) gg();
        }
        s.emplace(y, i);
    }
    if (cnt!=n-1)gg();
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
