#include <bits/stdc++.h>

using namespace std;
using ll=long long;

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline int get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

struct Query {
    int l, r;
    Query() {}
    Query(int _l, int _r) : l(_l), r(_r) {}
};

inline int64_t sqrt_ord(int l, int r) {
    static const int BLOCK_SIZE = 512;
    l /= BLOCK_SIZE;
    if (l&1) r = (1<<30) - r;
    return ((1ll*l)<<32) + r;
}
inline int _sqrt_ord(int l, int r) {
    static const int BLOCK_L = 9;
    static const int MAXN_L = 20;
    static const int MAXN = (1 << MAXN_L) - 1;
    l >>= BLOCK_L;
    if (l&1) r ^= MAXN;
    return (l<<MAXN_L) | r;
}
int64_t hilbert_ord(int x, int y, int pow=20, int rot=0) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? (y<hpow?0:3) : (y<hpow?1:2);
    (seg += rot) &= 3;
    static const int ROT_DELTA[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rot + ROT_DELTA[seg]) & 3;
    int64_t sub_square_size = 1ll << (2*pow-2);
    int64_t res = seg * sub_square_size;
    int64_t add = hilbert_ord(nx, ny, pow-1, nrot);
    res += (seg == 1 || seg == 2) ? add : (sub_square_size - add - 1);
    return res;
}
int _L;
template <typename F>
vector<int> reord(const vector<Query>& a, F f) {
    vector<int64_t> ord; ord.reserve(a.size());
    for (auto& q: a) {
        ord.emplace_back(f(q.l, q.r, _L, 0));
    }
    vector<int> id(a.size());
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return ord[u] < ord[v];
    });
    return id;
}

void solve() {
    int n,k;
    cin >> n >> k;
    _L = 32 - __builtin_clz(n);
    vector<int> co(n);
    for (auto& x: co) {
        cin >> x;
    }
    // compress, avoid of query log(X)
    Compress<ll> c;
    vector<int> a(n+1); ll sum = 0;
    vector<int> pre(n+1), nxt(n+1);
    a[0] = c.get_id(0);
    pre[0] = c.get_id(-k);
    nxt[0] = c.get_id(+k);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        if (co[i-1] == 2) x*=-1;
        sum += x;
        a[i] = c.get_id(sum);
        pre[i] = c.get_id(sum-k);
        nxt[i] = c.get_id(sum+k);
    }

    // sqrt-decomp
    int q; cin >> q;
    vector<Query> qry(q);
    for (int i = 0; i < q; i++) {
        int l,r;
        cin >> l >> r;
        l--;
        qry[i] = {l,r};
    }

    sum = 0;
    vector<int> cnt(3*n+6, 0);
    auto add_right = [&](int i){
        sum += cnt[pre[i]];
        cnt[a[i]]++;
    };
    auto rem_right = [&](int i){
        cnt[a[i]]--;
        sum -= cnt[pre[i]];
    };
    auto add_left = [&](int i){
        sum += cnt[nxt[i]];
        cnt[a[i]]++;
    };
    auto rem_left = [&](int i){
        cnt[a[i]]--;
        sum -= cnt[nxt[i]];
    };
    int l = 1, r = 0;
    auto adjust_seg = [&](int L, int R){
        while (l > L) {
            add_left(--l);
        }
        while (r < R) {
            add_right(++r);
        }
        while (l < L) {
            rem_left(l++);
        }
        while (r > R) {
            rem_right(r--);
        }
    };

    vector<ll> res(q);
    for (int i: reord(qry, hilbert_ord)) {
        int L = qry[i].l, R = qry[i].r;
        adjust_seg(L, R);
        res[i] = sum;
    }
    for (auto& x: res) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
