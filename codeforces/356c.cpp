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
#define dbg(args...) 2020
#endif

void solve() {
    int n; cin >> n;
    int cnt[5] = {};
    int sum = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        sum += x;
        cnt[x]++;
    }
    if (sum < 3 || sum == 5) { // proof omit
        cout << -1; return;
    }
    auto calc = [&](int i3, int i4){
        vector<pair<int, int>> a,b;
        for (int i = 0; i <= 4; i++) {
            if(cnt[i])a.emplace_back(i, cnt[i]);
        }
        if (i3+i4<n) b.emplace_back(0, n-i3-i4);
        if (i3) b.emplace_back(3, i3);
        if (i4) b.emplace_back(4, i4);
dbg(a, b);
        int diff = 0;
        while (!a.empty()) {
            assert(!b.empty());
            int da, ia;
            tie(da, ia) = a.back(); a.pop_back();
            int db, ib;
            tie(db, ib) = b.back(); b.pop_back();
            int x = min(ia, ib);
            diff += abs(da-db) * x;
            ia -= x; ib -= x;
            if (ia) a.emplace_back(da, ia);
            if (ib) b.emplace_back(db, ib);
        }
        return diff;
    };

    int lb = (sum+3)/4;
    int ub = min(n, sum/3);
    //cerr<<lb<<' '<<ub<<endl;
    int res = 1e8;
    // there're some greedy, (2,4), (1,2), (2,2,2)... cases. well we just brute force, with O(1) check
    for (int i = lb; i <= ub; i++) {
        int j = sum - i*3;
        res = min(res, calc(i-j, j));
    }
    res /= 2;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
