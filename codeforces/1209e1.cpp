#include <bits/stdc++.h>

using namespace std;

const int N = 4; 
const int M = 100; 
int a[N][M];

void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> mx(m);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            mx[j] = max(mx[j], a[i][j]);
        }
    }
    vector<int> id(m);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return mx[u] > mx[v];
    });
    m = min(n,m);
    vector<int> ofs;
    int res = 0;
    // brute force
    function<void(int)> dfs = [&](int x){
        if (x == m) {
            vector<int> tmp(n);
            for (int i = 0; i < n; i++) {
                for (int k = 0; k < m; k++) {
                    int j = id[k];
                    tmp[i] = max(tmp[i], a[(i+ofs[k])%n][j]);
                }
            }
            int sum = 0;
            for (int x:tmp) sum+=x;
            res = max(res, sum);
            return;
        }
        for (int k = 0; k < n; k++) {
            ofs.emplace_back(k);
            dfs(x+1);
            ofs.pop_back();
        }
    };
    dfs(0);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
