#include <bits/stdc++.h>

using namespace std;


// dynamic dp.
// valid iff each u, sum[u]<=depth[u], (depth reversed)
// best for c, (L-sum[0]) free all use c. 
// key optim: compress chain, thus goup step ~O(sqrt(n))
//  p - t - ... - i
//     top       low
// dp  cnt
// dp[u][c], max #c of arm of u
// cnt[t][c], #c of path p..i
void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> pa(n, -1), deg(n), depth(n);
    string co(n, '?');
    for (int i = 1; i < n; i++) {
        int p; char c;
        cin >> p >> c; --p;
        deg[p]++;
        depth[i] = depth[p] + 1;
        pa[i] = p;
        co[i] = c;
    }
    const int L = *max_element(depth.begin(), depth.end());
    for (int i = 0; i < n; i++) {
        if (deg[i]==0 && depth[i] < L) {
            for (int _ = 0; _ < q; _++) {
                cout << "Fou\n";
            }return;
        }
    }
    ++deg[0]; // virtual ensure deg[0]>1
    // compress
    vector<int> top(n);
    iota(top.begin(), top.end(), 0);
    vector<array<int,26>> dp(n), cnt(n);
    for (int i = 1; i < n; i++) {
        int p = pa[i];
        if (deg[p] == 1) {
            top[i] = top[p];
        }
        if (co[i] != '?') {
            cnt[top[i]][co[i]-'a']++;
        }
    }
    // prep dp
    vector<vector<int>> low(n);
    int bad = 0;
    for (int i = n-1; i >= 1; i--) {
        if (deg[i] != 1) {
            int t = top[i];
            int p = pa[t];
            for (int c = 0; c < 26; c++) {
                dp[p][c] = max(dp[p][c], dp[i][c] + cnt[t][c]);
            }
            low[p].push_back(i);
        }
    }
    // init sum
    for (auto& x:depth) x = L-x;
    vector<int> sum(n);
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            sum[i] += dp[i][c];
        }
        bad += sum[i] > depth[i];
    }

    auto update = [&](int i, int c){
        while (i != -1) {
            bad -= sum[i] > depth[i];
            sum[i] -= dp[i][c];
            dp[i][c] = 0;
            for (int v:low[i]) {
                dp[i][c] = max(dp[i][c], dp[v][c] + cnt[top[v]][c]);
            }
            sum[i] += dp[i][c];
            bad += sum[i] > depth[i];
            i = pa[top[i]];
        }
    };

    while (q--) {
        int i;char c;
        cin >> i >> c; --i;
        if (co[i] != '?') {
            cnt[top[i]][co[i]-'a']--;
            update(pa[top[i]], co[i]-'a');
        }
        co[i] = c;
        if (co[i] != '?') {
            cnt[top[i]][co[i]-'a']++;
            update(pa[top[i]], co[i]-'a');
        }

        if (bad > 0) {
            cout << "Fou\n";
        } else {
            cout << "Shi ";
            int res = 0;
            for (int c = 0; c < 26; c++) {
                res += (dp[0][c] + L - sum[0]) * (c+1);
            }
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
