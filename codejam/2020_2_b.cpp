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

struct State {
    int x, i;
    State() {}
    State(int _x, int _i) : x(_x), i(_i) {}
    bool operator<(const State& _oth) const {
        return x > _oth.x;
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> evs(n);
    vector<int> d(n);
    priority_queue<State> pq;
    for (int i = 1; i < n; i++) {
        cin >> d[i];
        if (d[i] < 0) {
            evs[-d[i]].push_back(i);
        } else {
            pq.emplace(d[i], i);
        }
    }
    vector<bool> les(n);
    les[0] = true;
    int cnt = 1;
    for (int c = 1; c < n; c++) if (!evs[c].empty()){
        // take into count
        while (cnt < c) {
            int i = pq.top().i; pq.pop();
            ++cnt; les[i] = true;
        }
        int mx = 0;
        for (int i = 0; i < n; i++) {
            if (les[i]) {
                mx = max(mx, d[i]);
            }
        }
        ++mx; // just +1, not more, otherwise there might be d<=mx in pq
        for (int i:evs[c]) {
            d[i] = mx;
            pq.emplace(d[i], i);
        }
    }
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        x = abs(d[x]-d[y]); // this form is fine
        if (!x) x = 1024; // weight>0
        cout << x << ' ';
    }
    cout << '\n';
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
