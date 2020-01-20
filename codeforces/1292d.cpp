#include <bits/stdc++.h>

using namespace std;

const int N = 5012;
int M  = 0;
int e[N][N]; // e, p^e of i!
int cnt[N];
void prep() {
    for (int i = 2; i <= M; i++) {
        int n = i;
        for (int x = 2; x*x <= n; x++) {
            while (n%x == 0) {
                e[i][x]++;
                n/=x;
            }
        }
        if (n>1) e[i][n]++;
        for (int j = 1; j <= M; j++) {
            e[i][j] += e[i-1][j];
        }
    }
}
using ll=long long;
// root-1 tree. pa[x] = x/lowp(x)
// let x = p0p0..p1...pk..
// then u is acens of x iff u is suffix(x)
// if in (one need compressed)trie, greedy explore node cnt > n/2.
void solve() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[x]++;
        M = max(M, x);
    }
    prep();
    ll res = 0;
    vector<int> last(M+1, 1); // max prime of holding i!
    for (int i = 1; i <= M; i++) {
        if (cnt[i] == 0) continue;
        for (int j = 1; j <= M; j++) {
            res += e[i][j] * 1ll * cnt[i];
            if (e[i][j]) last[i] = j;
        }
    }
    while (*max_element(last.begin(), last.end()) > 1) {
        vector<int> freq(M+1);
        for (int i = 1; i <= M; i++) {
            freq[last[i]] += cnt[i];
        }
        int p = max_element(freq.begin(), freq.end()) - freq.begin();
        if (p <= 1) break;
        if (freq[p] * 2 <= n) break;
        res -= (2*freq[p] - n);
        // update
        for (int i = 1; i <= M; i++) {
            // forbid/del
            if (last[i] != p) {
                last[i] = 1; continue;
            }
            // next last?
            e[i][p]--;
            while (last[i] > 1 && e[i][last[i]]==0) {
                --last[i];
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
