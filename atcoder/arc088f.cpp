#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    vector<int> deg(n+1);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        deg[x]++;
        deg[y]++;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    int root, cnt=0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1) cnt++;
        if (deg[i] == 1) root=i;// since it must be some end-point
    }
    // odd-deg as only end-point
    int A = cnt/2;
    int vir = 0; g[vir].emplace_back(root);
    auto ck = [&](int x){
        vector<int> dp(n+1); // len of remain path connect to u's p
        function<bool(int,int)> dfs = [&](int u, int p){
            vector<int> arm;
            for (int v: g[u])if(v!=p){
                if (!dfs(v, u)) return false;
                arm.emplace_back(dp[v]);
            }
            // we wanna pick small arm[i] for up using.
            // so bs on that, else [l,r] match check pair never > x
            if (arm.size()%2==0) arm.emplace_back(0);
            sort(arm.begin(), arm.end());
            int m = arm.size();
            int i = bs_first<int>(0, m, [&](int i){
                    int l=0, r=m-1;
                    while (l<r) {
                        if (l==i) l++;
                        if (r==i) r--;
                        if (l < r) {
                            if (arm[l] + arm[r] > x) return false;
                            l++; r--;
                        }
                    }
                    return true;
                    });
            if (i == m) return false;
            dp[u] = arm[i] + 1;
            if (u == root) {
                return dp[u] <= x+1;
            } else {
                return dp[u] <= x;
            }
        };
        return dfs(root, vir);
    };
    int B = bs_first<int>(1, n+1, ck);    
    cout << A << ' ' << B << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
