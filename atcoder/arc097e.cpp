#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

const int N = 2019; 
int b_as_back[N][N]; // append B in i+j. its inversion(cost)
int w_as_back[N][N];
int dp[N][N]; // i B, j W sorted in [i+j]. minimal inversion

void solve() {
    int n; cin >> n;
    vector<int> pos_b(n+1), pos_w(n+1);
    for (int i = 1; i <= 2*n; i++) {
        char c;int x;
        cin >> c >> x;
        if (c == 'B') pos_b[x] = i;
        if (c == 'W') pos_w[x] = i;
    }
    auto calc_base = [&](auto& pos){
        Fenwick<int> f(2*n);
        int sum = 0;
        for (int i = n; i >= 1; i--) {
            int p = pos[i];
            sum += f.query(p);
            f.add(p, 1);
        }
        return sum;
    };
    int base = calc_base(pos_b) + calc_base(pos_w);
    auto calc_cross = [&](auto& B, auto& W, auto& b){
        Fenwick<int> f(2*n);
        for (int j = n; j >= 0; j--) {
            for (int i = 1; i <= n; i++) {
                b[i][j] = f.query(B[i]);
            }
            if (j) f.add(W[j], 1);
        }
    };
    calc_cross(pos_b,pos_w,b_as_back);
    calc_cross(pos_w,pos_b,w_as_back);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (!i && !j) dp[i][j] = 0;
            if (!i) {dp[i][j] = dp[i][j-1]+w_as_back[j][i]; continue;}
            if (!j) {dp[i][j] = dp[i-1][j]+b_as_back[i][j]; continue;}
            dp[i][j] = min(dp[i-1][j]+b_as_back[i][j], dp[i][j-1]+w_as_back[j][i]);
        }
    }
    int res = dp[n][n] + base;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
