#include <bits/stdc++.h>

using namespace std;

const int N = 1024;
double bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]);
        }
    }
}
double f[N], convo[N];
//double c(int n, int k) {
//    double r = 1;
//    while (k > 0) {
//        r *= n--;
//        r /= k--;
//    }
//    return r;
//}
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a;
    vector<vector<int>> g(m);
    vector<int> sz(m), grt(m), eq(m);
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        sz[i] = k;
        for (int _ = 0; _ < k; _++) {
            int x; cin >> x;
            a.push_back(x);
            g[i].push_back(x);
        }
    }
    sort(a.begin(), a.end(), greater<int>());
    const int X = a[n-1]; 
    int all_grt = 0, all_eq = 0;
    for (int i = 0; i < m; i++) {
        for (int x:g[i]) {
            if (x > X) grt[i]++, all_grt++;
            if (x== X) eq[i]++, all_eq++;
        }
    }

    int sum = 0;
    convo[0] = 1;
    for (int _ = 0; _ < m; _++) {
        memcpy(f, convo, sizeof f);
        memset(convo, 0, sizeof convo);
        for (int i = 0; i <= sum; i++) {
            for (int j = 0; j <= eq[_]; j++) {
                convo[i+j] += f[i] / bino[sz[_]][grt[_] + j];
            }
        }
        sum += eq[_];
    }
    int need = n - all_grt;
    double res = convo[need];
    res /= bino[all_eq][need];
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    bino_table();
    solve();
    cout << endl;
}
