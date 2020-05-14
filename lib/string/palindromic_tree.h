#include <bits/stdc++.h>

using namespace std;

// basic fact, <=n different palin.
// tr forms two tree(even/odd)

// len:= max-len end with Ptr u, [      u]
// cnt:= #palin end with u, in above string
// fail:= suffix link, i.e. jump to repre next len'<len palin.
// sz:=#end as max-len.  => after dp (sz[fail[i]]+=sz[i]), sz[i]:=#occur

// SNIPPETS_START palindromic_tree
struct PalindromicTree {
    using T = char;
    using Ptr = int;
    T* s; int n;
    vector<array<Ptr,26>> tr;
    vector<Ptr> fail;
    vector<int> len, cnt, sz;
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
    }
};
// SNIPPETS_END
