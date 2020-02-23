#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int L = 20;
const int N = 400005; 
int nxt[L][N];
ll sum[L][N];
ll a[N];
ll check_add(const ll& x, const ll& y) {
    static const ll INF = 0x3f3f3f3f3f3f3f3f;
    if (x >= INF || y >= INF) return INF;
    if (x + y >= INF) return INF;
    return x + y;
}
void solve() {
    int n = 1;
    a[0] = 1e15;
    memset(sum, 0x3f, sizeof sum);
    sum[0][1] = 0;
    int q; cin >> q;
    ll res = 0;
    while (q--) {
        int op; ll x, y;
        cin >> op >> x >> y;
        x ^= res; y ^= res;
        assert(1 <= x && x <= n);
        if (op == 1) {
            // find first >=y
            a[++n] = y;
            if (a[n] <= a[x]) {
                nxt[0][n] = x;
            } else {
                for (int i = L-1; i >= 0; i--) {
                    if (a[nxt[i][x]] < a[n]) {
                        x = nxt[i][x];
                    }
                }
                nxt[0][n] = nxt[0][x];
            }
            // update nxt/sum
            sum[0][n] = a[n];
            for (int i = 1; i < L && nxt[i-1][n]; i++) {
                nxt[i][n] = nxt[i-1][ nxt[i-1][n] ];
                //sum[i][n] = sum[i-1][n] + sum[i-1][ nxt[i-1][n] ];
                sum[i][n] = check_add(sum[i-1][n], sum[i-1][ nxt[i-1][n] ]);
            }
        } else {
            res = 0;
            for (int i = L-1; i >= 0 && x; i--) {
                if (sum[i][x] <= y) {
                    res |= 1<<i;
                    y -= sum[i][x];
                    x = nxt[i][x];
                }
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
