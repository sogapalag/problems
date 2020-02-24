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

// https://sogapalag.github.io/2020/02/24/Optimization-Technique/
// below half-size suff would WA, since j might < 0, and those negative part has contribution too.
//   e.g. if j=0 => >d+5, then not include > d+1, d+2, 
// O(qn^.5 + n^1.5), no log
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    assert(m<n);
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<int> group(n, -1);
    vector<int> tour; tour.reserve(n);
    function<void(int,int)> get = [&](int u, int p){
        tour.push_back(u);
        for (int v:g[u])if(v!=p)get(v,u);
    };
    vector<int> arm(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        arm[u] = max(arm[u], depth);
        for (int v:g[u])if(v!=p){
            dfs(v,u, depth+1);
        }
    };
    vector<int> diam(n);
    vector<vector<double>> suff(n);
    vector<vector<double>> suff_of_suff(n);
    for (int i = 0; i < n; i++) {
        if (group[i] == -1) {
            tour.clear(); get(i, -1);
            for (auto& x: tour) {
                group[x] = i;
            }
            // calc arm
            dfs(i, -1, 0);
            int r = *max_element(tour.begin(), tour.end(), [&](int u, int v){
                    return arm[u] < arm[v]; });
            dfs(r, -1, 0);
            r = *max_element(tour.begin(), tour.end(), [&](int u, int v){
                    return arm[u] < arm[v]; });
            dfs(r, -1, 0);
            
            // prep suff freq
            for (int& u: tour) {
                diam[i] = max(diam[i], u = arm[u]);
            }
            sort(tour.begin(), tour.end());
            assert(tour[0] == (diam[i]+1)/2);
            /*
            suff[i].resize(diam[i] - tour[0] + 2);
            suff_of_suff[i].resize(diam[i] - tour[0] + 2);
            for (int x: tour) suff[i][x - tour[0]]++;
dbg(i, suff[i]);
            for (int j = suff[i].size() - 2; j >= 0; j--) {
                suff[i][j] += suff[i][j+1];
            }
            for (int j = suff[i].size() - 2; j >= 0; j--) {
                suff[i][j] /= suff[i][0];
                suff_of_suff[i][j] = suff_of_suff[i][j+1] + suff[i][j];
            }
dbg(suff[i], suff_of_suff[i]);
            */
            suff[i].resize(diam[i] + 2);
            suff_of_suff[i].resize(diam[i] + 2);
            for (int x: tour) suff[i][x]++;
            for (int j = suff[i].size() - 2; j >= 0; j--) {
                suff[i][j] += suff[i][j+1];
            }
            for (int j = suff[i].size() - 2; j >= 0; j--) {
                suff[i][j] /= suff[i][0];
                suff_of_suff[i][j] = suff_of_suff[i][j+1] + suff[i][j];
            }
        }
    }

    map<pair<int,int>, double> mp;
    auto calc = [&](int u, int v){
        u = group[u]; v = group[v];
        if (u == v) {
            cout << "-1\n";
            return;
        }
        if (diam[u] > diam[v] || (diam[u] == diam[v] && u > v)) swap(u,v);
        if (mp.find({u,v}) != mp.end()) {
            double res = mp[{u,v}];
            cout << res << '\n';
            return;
        }
        double sum = 0;
        for (int i = 0; i < (int)suff[u].size()-1; i++) {
            double x = suff[u][i] - suff[u][i+1];
            int j = diam[v] - i;
            j = max(j, 0);
            assert(j < (int)suff[v].size());
            sum += x * suff_of_suff[v][j];
        }
        sum += diam[v];
        mp[{u,v}] = sum;
        cout << fixed << setprecision(10) << sum << '\n';
    };

    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        calc(x,y);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
