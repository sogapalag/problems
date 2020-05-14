#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct PalindromicTree {
    using T = char;
    using Ptr = int;
    T* s; int n;
    vector<array<Ptr,26>> tr;
    vector<Ptr> fail;
    vector<int> len, cnt;
    vector<int> sz;
    Ptr vc, crt;
    PalindromicTree(T* _s, int _n)
        : s(_s)
        , n(_n)
        , tr(n + 2)
        , fail(n + 2)
        , len(n + 2)
        , cnt(n + 2)
        , sz(n + 2)
        {
        build();
    }
    void build() {
        fail[0] = 1; len[1] = -1;
        vc = 2; crt = 1;
        s[0] = '$';
        for (int i = 1; i <= n; i++) {
            int c = s[i] - 'a';
            Ptr u = crt;
            while (s[i-len[u]-1] != s[i]) u = fail[u];
            if (!tr[u][c]) {
                Ptr v = fail[u];
                while (s[i-len[v]-1] != s[i]) v = fail[v];
                cnt[vc] = cnt[fail[vc] = tr[v][c]] + 1;
                len[tr[u][c] = vc] = len[u] + 2; // must below, v could = u result fail[vc]=vc.
                ++vc;
            }
            crt = tr[u][c];
            ++sz[crt];
        }
        ll res = 0;
        // note a palin #occur = (sz=#end as max-len) + (#end less max-len = in fail)
        for (int i = vc-1; i >= 2; i--) {
            if (fail[i] > 1) {
                sz[fail[i]] += sz[i];
            }
            res = max(res, sz[i]*1ll*len[i]);
        }
        cout << res;
    }
};

const int N = 3e5+10; 
char s[N];
void solve() {
    cin >> (s+1);
    int n = strlen(s+1);
    PalindromicTree pt(s,n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
