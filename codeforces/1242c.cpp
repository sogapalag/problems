#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

// perm, form with cycle. dp SoS
void solve() {
    int n; cin >> n;
    map<int, int> mp;
    ll S = 0;
    vector<ll> row(n, 0);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
            int x; cin >> x;
            S += x;
            row[i] += x;
            mp[x] = i;
        }
    }
    if (S % n != 0) {
        cout << "No"; return;
    }
    S /= n;

    vector<bool> dp(1<<n, false);
    vector<vector<pair<int,int>>> certs(1<<n);
    auto explore = [&](int x, int i){
        vector<pair<int, int>> res;
        res.emplace_back(x, i);
        int msk = 0;
        while (true) {
            int x,i;
            tie(x,i) = res.back();
            msk |= 1<<i;
            ll y = x + S - row[i];
            if (abs(y) > 1e9) return;
            auto it = mp.find(y);
            if (it == mp.end()) return;
            x = y; i = it->second;
            if (msk & (1<<i)) {
                if (!dp[msk] && x == res[0].first && i == res[0].second) {
                    dp[msk] = true;
                    for (auto& p: res) {
                        certs[msk].emplace_back(p.first, p.second);
                    }
                }
                return;
            } else {
                res.emplace_back(x, i);
            }

        }
    };
    for (auto& p: mp) {
        int x,i;
        tie(x,i) = p;
        if (row[i] == S) {
            if (!dp[1<<i]) {
                dp[1<<i] = true;
                certs[1<<i].emplace_back(x,i);
            }
        } else {
            explore(x,i);
        }
    }
dbg(certs);
    const int MSK = 1<<n; 
    for (int msk = 1; msk < MSK; msk++) {
        if (dp[msk]) continue;
        for (int sub = msk-1; sub > 0; (sub-=1)&=msk) {
            if (dp[sub] && dp[msk^sub]) {
                dp[msk] = true; break;
            }
        }
    }
    if (!dp[MSK-1]) {
        cout << "No"; return;
    }
    cout << "Yes\n";
    vector<pair<int, int>> res(n);
    function<void(int)> dfs = [&](int msk){
        if (msk == 0) return;
        if (!certs[msk].empty()) {
            int m = certs[msk].size();
            for (int i = 0; i < m; i++) {
                int x, fr;
                tie(x, fr) = certs[msk][i];
                int to = certs[msk][(i+m-1)%m].second;
                res[fr] = {x, to+1};
            }
            return;
        }
        for (int sub = msk-1; sub > 0; (sub-=1)&=msk) {
            if (dp[sub] && dp[msk^sub]) {
                dfs(sub);
                dfs(msk^sub);
                return;
            }
        }
    };
    dfs(MSK-1);
    for (auto& p: res) {
        cout << p.first << ' ' << p.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
