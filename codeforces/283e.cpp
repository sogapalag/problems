#include <bits/stdc++.h>

using namespace std;

// LazySegTree template code by : hitonanode
template <typename VAL, typename DVAL>
struct LazySegTree
{
    int N;
    int head;

    vector<VAL> val;
    vector<DVAL> dval;
    VAL I_val;
    DVAL I_dval;

    using vv2v = function<VAL(const VAL&, const VAL&)>;
    using d2d = function<void(DVAL&, const DVAL&)>;
    using d2v = function<void(VAL&, const DVAL&)>;
    vv2v merge_val;
    d2d add_dval;
    d2v refl_dval;

    LazySegTree(vector<VAL> &val_init, VAL val_default, DVAL dval_default,
                vv2v f, d2d dadd, d2v dreflect)
            : N(val_init.size()), I_val(val_default), I_dval(dval_default),
              merge_val(f),
              add_dval(dadd),
              refl_dval(dreflect)
    {
        int N_tmp = 1;
        while (N_tmp < N) N_tmp <<= 1;
        val = vector<VAL>(N_tmp*2, I_val);
        dval = vector<DVAL>(N_tmp*2, I_dval);
        head = N_tmp - 1;
        for (int i=0; i<N; i++) val[head+i] = val_init[i];
        for (int pos=head-1; pos>=0; pos--) val[pos] = merge_val(val[pos*2+1], val[pos*2+2]);
    }

    void resolve_dval(int pos, int l, int r) { // posで遅延を解消して子孫に押し付ける
        refl_dval(val[pos], dval[pos]);
        if (pos < head)
        {
            add_dval(dval[pos*2+1], dval[pos]);
            add_dval(dval[pos*2+2], dval[pos]);
        }
        dval[pos] = I_dval;
    }

    void update(int begin, int end, DVAL dval_q) { update(begin, end, dval_q, 0, 0, head+1); }
    void update(int begin, int end, DVAL dval_q, int pos, int l, int r)
    {
        // 後でリファクタリング
        if (begin <= l && r <= end) { // 担当区間全部使う
            add_dval(dval[pos], dval_q);
            resolve_dval(pos, l, r);
        }
        else if (begin < r && l < end) { // 少なくともどこかで交差
            resolve_dval(pos, l, r);
            update(begin, end, dval_q, pos*2+1, l, (l+r)/2);
            update(begin, end, dval_q, pos*2+2, (l+r)/2, r);
            val[pos] = merge_val(val[pos*2+1], val[pos*2+2]);
        }
        else resolve_dval(pos, l, r);
    }

    VAL getvalue(int begin, int end) { return getvalue(begin, end, 0, 0, head+1); }
    VAL getvalue(int begin, int end, int pos, int l, int r)
    {
        resolve_dval(pos, l, r);
        if (begin <= l && r <= end) return val[pos];
        else if (begin<r && l<end) {
            VAL vl = getvalue(begin, end, pos*2+1, l, (l+r)/2);
            VAL vr = getvalue(begin, end, pos*2+2, (l+r)/2, r);
            val[pos] = merge_val(val[pos*2+1], val[pos*2+2]);
            return merge_val(vl, vr);
        }
        else return I_val;
    }
};
// END of LazySegTree template code by : hitonanode
using ll=long long;

// recall 1264e, similar (n,3) - sum (out/indeg,2)
// note by matrix view, each time we flip a diag-square. but this won't help.
// let's focus on how to count outdeg of i. note only segs contain i matter, to i's deg. and j!=i that by covered parity indicate j-i direction.
// thus we linear-sweep, maintain range(0,1) sum.(one can maintain only 0, but need seg-len, since #0+#1=len)
//   as long as we remember to calcel segs out of i, 
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<vector<int>> evs(n+1);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y; y++;
        x = lower_bound(a.begin(), a.end(), x) - a.begin();
        y = lower_bound(a.begin(), a.end(), y) - a.begin();
        if (x < n && x < y) {
            evs[x].emplace_back(y);
            evs[y].emplace_back(x);
        }
    }
    using T = array<int,2>;
    vector<T> leaves(n, {1,0});
    LazySegTree<T, int> rsum_flip (leaves, {0,0}, 0,
            [](T u, T v){ return T{u[0]+v[0], u[1]+v[1]}; },
            [](int& x, int y) { x ^= y; },
            [](T& u, int x) { if(x) swap(u[0],u[1]), x=0; }
            );
    ll res = 1ll*n*(n-1)*(n-2)/6;
    for (int i = 0; i < n; i++) {
        for (int r: evs[i]) {
            if (r > i) rsum_flip.update(i, r, 1);
            else rsum_flip.update(r, i, 1);
        }
        ll deg = rsum_flip.getvalue(0, i)[0] + rsum_flip.getvalue(i+1, n)[1];
        res -= deg*(deg-1)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
