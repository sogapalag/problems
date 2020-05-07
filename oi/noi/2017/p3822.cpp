#include <bits/stdc++.h>

using namespace std;

using ll=long long;
#define int ll
const int B = 60;
const int MSK = 1ll<<B;
const int MSK1 = MSK-1;

using i8=int8_t;
using M=array<i8,2>;
const int MX = 1<<20; 
    M a[MX<<1];
    i8 d[MX];
    int num[MX];
template <typename M, typename D>
struct SegLazy {
    using Op = function<M(const M&, const M&)>;
    using D2M = function<void(M&, const D&)>;
    using D2D = function<void(D&, const D&)>;
    
    M ID;
    D UN;
    Op op;
    D2M d2m;
    D2D d2d;

    int N, L;
    //vector<M> a; // tree
    //vector<D> d; // lazy
    //vector<int> num;
    

    SegLazy(int n, M leaf_default, M _ID, D _UN, Op _op, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op), d2m(_d2m), d2d(_d2d)
    {
        init_space(n);
        //fill(a.begin() + N, a.begin() + N + n, leaf_default);
        fill(a+N, a+N+n, leaf_default);
        build();
    }
    void init_space(int n) {
        N = 1; L = 0; while (N < n) N <<= 1, L++;
        //a.assign(N<<1, ID);
        //d.assign(N, UN);
        //num.assign(N, 0);
        fill(a, a+(N<<1), ID);
        memset(d, -1, sizeof d);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }
    inline int len(int i) {
        return 1 << (L + __builtin_clz(i) - 31);
    }
    inline void apply(int i, const D& dval) {
        d2m(a[i], dval);
        if (i < N) d2d(d[i], dval);
        else if (dval != UN) {
            //cerr<<i-N<<' '<<dval<<endl;
            num[i-N] = dval ? MSK1 : 0;
        }
    }
    inline void push(int i) {
        if (d[i]==UN) return; // 2x faster
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = UN;
    }
    void update(int l, int r, const D& dval, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        if (l <= sl && sr <= r) return apply(i, dval);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        update(l, r, dval, il, sl, sm);
        update(l, r, dval, ir, sm, sr);
        pull(i);
    }
    M query(int l, int r, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return ID;
        if (l <= sl && sr <= r) return a[i];
        push(i);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        return op(query(l, r, il, sl, sm), query(l, r, ir, sm, sr));
    }

    void update(int l, int r, const D& dval) { 
        assert(0 <= l && r <= N);
        update(l, r, dval, 1, 0, N);
    }
    void assign(int p, const M& x) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        for (a[p] = x; p >>= 1; ) pull(p);

    }
    M query(int l, int r) {
        assert(0 <= l && r <= N);
        return query(l, r, 1, 0, N);
    }
    M query_point(int p) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        return a[p];
    }
    M query_all() const { return a[1]; }

    int find(int l, int o, int i, int sl, int sr) {
        if (sr <= l || !a[i][o]) return -1;
        if (sr-sl==1) {
            return a[i][o] ? i-N : -1;
        }
        push(i);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        int res = -1;
        if (l < sm) res = find(l, o, il, sl, sm);
        return res != -1 ? res : find(l, o, ir, sm, sr);
    }
    // find first>=l block contain o
    int find(int l, int o) {
        return find(l,o,1,0,N);
    }

    // update goup from p
    inline void up(int p) {
        a[p+N][0] = num[p] != MSK1;
        a[p+N][1] = num[p] != 0;
        p += N;
        for (; p >>= 1; ) pull(p);
    }
    // += x2^p
    void add(int x, int p) {
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        p -= N;
        num[p] += x;
        if (num[p]>>B&1) {
            num[p]^=MSK;
            int i = find(p+1, 0);
            update(p+1, i, 0);
            num[i] += 1;
            up(i);
        }
        up(p);
    }
    // -= x2^p
    void sub(int x, int p) {
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        p -= N;
        num[p] -= x;
        if (num[p] < 0) {
            num[p]+=MSK;
            int i = find(p+1, 1);
            //cerr<<i<<endl;
            update(p+1, i, 1);
            num[i] -= 1;
            up(i);
        }
        up(p);
    }
    inline int bit(int i) {
//dbg(a,d,num);
        int p = i/B, r = i%B;
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        p -= N;
        //cerr<<num[p]<<endl;
        return num[p]>>r&1;
    }
};

int getint()
{
    int i=0,f=1;char c;
    for(c=getchar();(c!='-')&&(c<'0'||c>'9');c=getchar());
    if(c=='-')c=getchar(),f=-1;
    for(;c>='0'&&c<='9';c=getchar())i=(i<<3)+(i<<1)+c-'0';
    return i*f;
}

// max score 84/100. 4 cases TLE.
// need some constant-optim.
// => LL,B=62, max. 92/100. 2TLE
// => LL,B=60, '%'=>'&', inline some func, add check push(this part matter), 100/100
void solve() {
    int n,_t1,_t2,_t3;
    cin >> n >> _t1 >> _t2 >> _t3;
    //scanf("%d%d%d%d", &n,&_t1,&_t2,&_t3);
    //n=getint();_t1=getint();_t2=getint();_t3=getint();
    SegLazy<M,i8> seg(n, {1,0}, {0,0}, -1,
            [](M u, M v){
            M r;
            r[0] = u[0]|v[0];
            r[1] = u[1]|v[1];
            return r;
            },
            [](M& u, i8 x){
            if (x != -1) u[x] = 1, u[x^1] = 0;
            },
            [](i8& x, i8 y){
            if (y != -1) x = y; // !ERR 0/1 = -1
            });
    for (int _ = 0; _ < n; _++) {
        int op; cin >> op;
        if (op == 1) {
            int a,b;
            cin >> a >> b;
            //scanf("%d%d",&a,&b);
            //a=getint();b=getint();
            int r = b%B;
            int x = (1LL<<(B-r)) - 1;
            if (a > 0) {
                seg.add((a&x)<<r , b/B); // 60, 1ll
                seg.add(a>>(B-r), b/B+1);
            } else if(a < 0) {
                a *= -1;
                seg.sub((a&x)<<r , b/B);
                seg.sub(a>>(B-r), b/B+1);
            }
        } else {
            int k; cin >> k;
            //scanf("%d",&k);
            //k=getint();
            seg.bit(k)?puts("1"):puts("0");
            //printf("%d\n",seg.bit(k));
            //cout << seg.bit(k) << "\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
