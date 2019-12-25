#include <bits/stdc++.h>

using namespace std;

template <int N>
struct DenseScc {
    int n;
    vector<bitset<N>> g;
    vector<int> deg;
    DenseScc(int _n) : n(_n), g(n), deg(n, 0) {
        input();
    }
    void input() {
        for (int i = 0; i < n; i++) {
            string s;cin >> s;
            for (int j = 0; j < n; j++) {
                if (i==j)continue;
                if (s[j]=='1') {
                    deg[i]++;
                    g[i][j]=1;
                }
            }
        }
    }

    void flip_adj(int i){
        for (int j = 0; j < n; j++) {
            if (i==j)continue;
            if (g[i][j]) {
                deg[i]--;deg[j]++;
            } else {
                deg[i]++;deg[j]--;
            }
            g[j].flip(i);
        }
        g[i].flip();
    }
    bool is_scc() {
        auto d = deg;
        sort(d.begin(), d.end(), greater<int>());
        int sum = 0;
        for (int i = 0; i < n-1; i++) {
            sum += d[i];
            // all out
            if (sum - (i+1)*i/2 == (i+1)*(n-i-1)) return false;
        }
        return true;
    }
};

void solve() {
    int n; cin >> n;
    DenseScc<2048> g(n);

    if (g.is_scc()) {
        cout << "0 1"; return;
    }
    
    if (n <= 6) {
        int mi = 1000, way = 0;
        for (int msk = 1; msk < 1<<n; msk++) {
            for (int i = 0; i < n; i++) {
                if(msk>>i&1) g.flip_adj(i);
            }
            int x = __builtin_popcount(msk);
            if (g.is_scc()) {
                if (x < mi) {
                    mi = x; way = 1;
                }else if (x==mi){
                    way++;
                }
            }

            for (int i = 0; i < n; i++) {
                if(msk>>i&1) g.flip_adj(i);
            }
        }
        if (mi==1000){
            cout << -1;
        } else {
            cout << mi << ' '<< mi*way;
        }
    } else {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            g.flip_adj(i);
            if (g.is_scc()) cnt++;
            g.flip_adj(i);
        }
        cout << "1 " << cnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
