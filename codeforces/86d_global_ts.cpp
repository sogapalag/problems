#include <bits/stdc++.h>

using namespace std;

inline int read()
{
	register int x=0,f=1;register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
inline void write(register long long x)
{
	if(!x)putchar('0');if(x<0)x=-x,putchar('-');
	static int sta[25];int tot=0;
	while(x)sta[tot++]=x%10,x/=10;
	while(tot)putchar(sta[--tot]+48);
}

using ll=long long;
const int N = 2e5+10; 
const int X = 1e6+10; 
int b[N];
//const int block_size = 512;
int block_size;
struct Query {
    int l, r, i;
    Query() {}
    Query(int _l, int _r, int _i) : l(_l), r(_r), i(_i) {}
    inline bool operator<(const Query& _oth) const {
        return b[l] == b[_oth.l] ? ((b[l]&1)? r > _oth.r : r < _oth.r) : l < _oth.l;
    }
}qry[N];


//inline int64_t sqrt_ord(int l, int r) {
//    static const int BLOCK_SIZE = 512;
//    //l /= BLOCK_SIZE;
//    l /= block_size;
//    if (l&1) r = (1<<30) - r;
//    return ((1ll*l)<<32) + r;
//}
//inline int _sqrt_ord(int l, int r) {
//    static const int BLOCK_L = 9;
//    static const int MAXN_L = 20;
//    static const int MAXN = (1 << MAXN_L) - 1;
//    l >>= BLOCK_L;
//    if (l&1) r ^= MAXN;
//    return (l<<MAXN_L) | r;
//}
//int64_t hilbert_curve(int x, int y, int pow, int rot) {
//    if (pow == 0) return 0;
//    int hpow = 1 << (pow-1);
//    int seg = (x < hpow) ? (y<hpow?0:3) : (y<hpow?1:2);
//    (seg += rot) &= 3;
//    static const int ROT_DELTA[4] = {3, 0, 0, 1};
//    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
//    int nrot = (rot + ROT_DELTA[seg]) & 3;
//    int64_t sub_square_size = 1ll << (2*pow-2);
//    int64_t res = seg * sub_square_size;
//    int64_t add = hilbert_curve(nx, ny, pow-1, nrot);
//    res += (seg == 1 || seg == 2) ? add : (sub_square_size - add - 1);
//    return res;
//}
//int _POW; // = 32 - clz(n)
//inline int64_t hilbert_ord(int l, int r) {
//    return hilbert_curve(l, r, 20, 0);
//}
//template <typename F>
//vector<int> reord(const vector<Query>& a, F f) {
//    vector<int64_t> ord; ord.reserve(a.size());
//    for (auto& q: a) {
//        ord.emplace_back(f(q.l, q.r));
//    }
//    vector<int> id(a.size());
//    iota(id.begin(), id.end(), 0);
//    sort(id.begin(), id.end(), [&](auto& u, auto& v){
//        return ord[u] < ord[v];
//    });
//    return id;
//}

int n,q;
int a[N];
int cnt[X];
ll sum = 0;
int l = 0, r = -1;
//inline void add_left (int i){
//    sum += (ll)(2*cnt[a[i]]+1) * a[i];
//    cnt[a[i]]++;
//}
//inline void add_right (int i){
//    sum += (ll)(2*cnt[a[i]]+1) * a[i];
//    cnt[a[i]]++;
//}
//inline void rem_left (int i){
//    cnt[a[i]]--;
//    sum -= (ll)(2*cnt[a[i]]+1) * a[i];
//}
//inline void rem_right (int i){
//    cnt[a[i]]--;
//    sum -= (ll)(2*cnt[a[i]]+1) * a[i];
//}
//inline void adjust_seg (int L, int R){
//    while (l > L) {
//        add_left(--l);
//    }
//    while (r < R) {
//        add_right(++r);
//    }
//    while (l < L) {
//        rem_left(l++);
//    }
//    while (r > R) {
//        rem_right(r--);
//    }
//}
inline void add_left (register ll x){
    sum += (cnt[x]+cnt[x]+1) * x;
    ++cnt[x];
}
inline void add_right (register ll x){
    sum += (cnt[x]+cnt[x]+1) * x;
    ++cnt[x];
}
inline void rem_left (register ll x){
    --cnt[x];
    sum -= (cnt[x]+cnt[x]+1) * x;
}
inline void rem_right (register ll x){
    --cnt[x];
    sum -= (cnt[x]+cnt[x]+1) * x;
}
inline void adjust_seg (int L, int R){
    while (l > L) {
        add_left(a[--l]);
    }
    while (r < R) {
        add_right(a[++r]);
    }
    while (l < L) {
        rem_left(a[l++]);
    }
    while (r > R) {
        rem_right(a[r--]);
    }
}
//...
void solve() {
    //cin >> n >> q;
    n = read(), q = read();
    //_POW = 32 - __builtin_clz(n);
    block_size = sqrt(n) + 1;
    for (int i = 1; i <= n; i++) {
        //cin >> a[i];
        a[i] = read();
        b[i] = i/block_size;
    }

    //vector<Query> qry(q);
    for (int i = 0; i < q; i++) {
        qry[i].l=read(),qry[i].r=read();
        qry[i].i=i;
        //cin >> l >> r;
        //l--;
        //qry[i] = {l,r, i};
    }


    sort(qry, qry+q);
    vector<ll> res(q);
    for (int i = 0; i < q; i++) {
        //adjust_seg(qry[i].l, qry[i].r);
        int L = qry[i].l, R = qry[i].r;
        while (l > L) {
            add_left(a[--l]);
        }
        while (r < R) {
            add_right(a[++r]);
        }
        while (l < L) {
            rem_left(a[l++]);
        }
        while (r > R) {
            rem_right(a[r--]);
        }
        res[qry[i].i] = sum;
    }
    //for (int i: reord(qry, hilbert_ord)) {
    //    int L = qry[i].l, R = qry[i].r;
    //    adjust_seg(L, R);
    //    res[i] = sum;
    //}
    for (auto& x: res) {
        //cout << x << "\n";
        write(x), printf("\n");
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    solve();
    return 0;
    //cout << endl;
}
