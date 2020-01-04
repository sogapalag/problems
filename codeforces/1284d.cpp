#include <bits/stdc++.h>

using namespace std;
using vpi = vector<pair<int, int>>;
#define fi first
#define se second

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 19; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] < raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
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
        return raw[query_id(l, r)];
    }
};
template <typename T=int>
struct Rmq2 {
    vector<T> raw;
    static const int LOG = 19; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq2(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] > raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
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
        return raw[query_id(l, r)];
    }
};

struct Node {
    int x, y, u, v;
    Node() {}
    Node(int _x, int _y, int _u, int _v) : x(_x), y(_y), u(_u), v(_v) {}
};

// check pairwise, overlap in A, and not in B.
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> A(n), B(n);
    for (int i = 0; i < n; i++) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        A[i] = {x,y};
        B[i] = {u,v};
    }
    //sort(a.begin(), a.end());
    //sort(b.begin(), b.end());

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return A[u].fi<A[v].fi || (A[u].fi==A[v].fi && A[u].se<A[v].se);
    });
    vector<pair<int, int>> a(n),b(n);
    for (int i = 0; i < n; i++) {
        a[i] = A[id[i]];
        b[i] = B[id[i]];
    }
    auto ck = [&](){
        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            l[i] = b[i].fi;
            r[i] = b[i].se;
        }
        Rmq<> mi(r);
        Rmq2<> mx(l);
        for (int i = 0; i < n; i++) {
            int x,y;
            tie(x,y) = a[i];
            int j = lower_bound(a.begin(), a.end(), make_pair(y+1,-1)) - a.begin();
            tie(x,y) = b[i];
            if (mi.query(i, j) < x || mx.query(i, j) > y) return false;
        }
        return true;
    };
    bool res = ck();
    if (res) {
        swap(A,B);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return A[u].fi<A[v].fi || (A[u].fi==A[v].fi && A[u].se<A[v].se);
        });
        // noob
        //vector<pair<int, int>> a(n),b(n);
        for (int i = 0; i < n; i++) {
            a[i] = A[id[i]];
            b[i] = B[id[i]];
        }
        res &= ck();
    }
    cout << (res?"YES":"NO");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
