#include <bits/stdc++.h>

using namespace std;

// sparse table RMQ. insight, st[j][i], cover [i, i+(1<<j) )
// unlike normal RMQ, use [j][i], not [i][j]. and store the index not actual element.
// query [l, r)

// SNIPPETS_START rmq
template <typename T=int>
struct Rmq {
    vector<T> a;
    int n, L;
    vector<vector<int>> st;
    Rmq(vector<T> _a) : a(_a) { // pass in vec[0, n)
        n = a.size();
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return a[x] < a[y] ? x : y;
    }
    void build() {
        L = 32 - __builtin_clz(n);
        st.resize(L);
        for (int j = 0; j < L; j++) {
            st[j].resize(n);
        }
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < L; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return a[query_id(l, r)];
    }
};
// SNIPPETS_END
