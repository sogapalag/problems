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

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n), which(n);
    vector<int> len(n);
    vector<int> cnt(n);
    for (int i = 1; i < n; i++) {
        cin >> len[i];
        for (int _ = 0; _ < len[i]; _++) {
            int x; cin >> x; --x;
            cnt[x]++;
            g[i].push_back(x);
            which[x].push_back(i);
        }
    }

    vector<int> del(n);
    vector<int> a(n);
    auto ck = [&](int r, int a0, auto cnt, auto del){
        // fix a0, remain should unique
        a[0] = a0; cnt[a0] = 0;
        for (int i = r; i >= 1; i--) {
            int x = -1;
            for (int y = 0; y < n; y++) {
                if (cnt[y] == 1) x = y;
            }
            if (x == -1) return false;
            
            a[i] = x;
            int k = -1; for (int kk: which[x]) if (!del[kk]) k = kk;
            del[k] = true;
            for (int y: g[k]) --cnt[y];
        }
        return true;
    };
    for (int i = n-1; i >= 1; i--) {
        vector<int> candi;
        for (int x = 0; x < n; x++) {
            if (cnt[x] == 1) candi.push_back(x);
        }
        if (candi.size() == 2) {
            int u = candi[0], v = candi[1];
            // seg has l must has r too.
            if (which[u].size() > which[v].size()) swap(u,v);
            ck(i,u,cnt,del) || ck(i,v,cnt,del);
            break;
        }
        int x = candi[0];
        a[i] = x;
        int k = -1; for (int kk: which[x]) if (!del[kk]) k = kk;
        del[k] = true;
        for (int y: g[k]) --cnt[y];
    }
    for (int x: a) cout << x+1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
