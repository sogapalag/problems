#include <bits/stdc++.h>

using namespace std;

const int S = 2e7; 
int ch[2][S], pa[S], rk[S], a[S];
// time: O(m L^2 a(n))
// space: exactly S = 2N + 2*(#successful-join)*(L+1)
struct PersistentDsu {
    using Ptr = int;
    using Index = int;
    int n, L, N;
    //vector<Ptr> ch[2];
    //vector<Index> pa;
    //vector<int> rk;
    int* raw;
    //vector<int> a;
    Ptr vc = 1;
    PersistentDsu(int _n, int* _r) : n(_n), raw(_r) {
        L = 1; N = 2;
        while (N < n) ++L, N <<= 1;
        //int S = 2*N + 2*n*(L+1);
        //ch[0].resize(S);
        //ch[1].resize(S);
        //pa.resize(S);
        //rk.resize(S);
        //a.resize(S);
        build();
    }
    void build() {
        for (int i = 2*N-1; i >= N; i--) {
            pa[i] = i-N;
            if (i<n+N) a[i] = raw[i-N];
        }
        for (int i = N-1; i >= 1; i--) {
            ch[0][i] = i<<1;
            ch[1][i] = i<<1|1;
        }
        vc = 2*N;
    }
    Ptr find_ptr(Ptr v, Index x) {
        for (int i = L-1; i >= 0; i--) {
            v = ch[x>>i&1][v];
        }
        return v;
    }
    // pa[x]=p
    Ptr update(Ptr v, Index x, Index p) {
        for (int i = L-1; i >= 0; i--) {
            int b = x>>i&1;
            ch[b^1][vc] = ch[b^1][v];
            ch[b][vc] = vc+1; ++vc;
            v = ch[b][v];
        }
        pa[vc] = p;
        rk[vc] = rk[v];
        // any more info here.
        a[vc] = a[v];
        return vc++ - L;
    }
    // find root pa[v]=x, still return v not pa.
    Ptr find(Ptr _, Index x) {
        auto v = find_ptr(_,x);
        while (pa[v] != x) v = find_ptr(_,x = pa[v]);
        return v;
        //return pa[v] == x ? v : find(_,pa[v]);
    }
    Ptr join(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        if (pa[x] == pa[y]) return _;
        if (rk[x] < rk[y]) swap(x,y);
        auto v = update(_,pa[y],pa[x]); y = vc-1;
        // can possibly omit if no merge, save half-space
        // although ++rk[x] might affect past, but most cases no big deal.
        v = update(v,pa[x],pa[x]); x = vc-1;
        if (rk[x] == rk[y]) ++rk[x];
        // merge here
        a[x] = min(a[x], a[y]);
        return v;
    }
    bool check(Ptr _, Index x, Index y) {
        x = find(_,x);
        y = find(_,y);
        return pa[x] == pa[y];
    }
    int ans(Ptr _, Index x) {
        x = find(_,x);
        return a[x];
    }
};
struct State {
    int d,x;
    State() {}
    State(int _d, int _x) : d(_d), x(_x) {}
    bool operator<(const State& _oth) const {
        return d > _oth.d;
    }
};
// test io
#define UI unsigned int
#define RG register
#define I inline
#define R RG UI
#define G c=getchar()
I UI in(){
	RG char G;
	while(c<'-')G;
	R x=c&15;G;
	while(c>'-')x*=10,x+=c&15,G;
	return x;
}
// recur-dsu: max 76/100, 4/16 TLE
// iter-dsu: 88/100, 2/16 TLE
// iter-dsu + fast io: 100/100 AC.
// iter-dsu-merge: 64/100, 6/16 TLE. more space, more time? maybe some impl problem
void solve() {
    int n,m;
    //cin >> n >> m;
    n=in();m=in();
    vector<tuple<int,int,int>> es(m);
    vector<vector<pair<int,int>>> g(n);
    vector<int> Hs(m);
    for (int i = 0; i < m; i++) {
        int x,y,z,h;
        //cin >> x >> y >> z >> h;
        x=in(),y=in(),z=in(),h=in();
        --x;--y;
        es[i] = {x,y,h};
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
        Hs[i] = h;
    }

    vector<int> d(n,2e9+10);
    priority_queue<State> pq;
    pq.emplace(d[0]=0, 0);
    while (!pq.empty()) {
        auto _ = pq.top(); pq.pop();
        int z = _.d, x = _.x;
        if (d[x] < z) continue;
        for (auto [y,w]: g[x]) {
            if (d[y] > z+w) {
                d[y] = z+w;
                pq.emplace(d[y],y);
            }
        }
    }

    sort(Hs.begin(), Hs.end());
    Hs.erase(unique(Hs.begin(), Hs.end()), Hs.end());
    auto pos = [&](int x){
        return lower_bound(Hs.begin(), Hs.end(), x) - Hs.begin();
    };
    int sz = Hs.size();
    vector<vector<pair<int,int>>> evs(sz);
    for (auto [x,y,h]:es) {
        evs[pos(h)].emplace_back(x, y);
    }
    PersistentDsu dsu(n,&d[0]);
    vector<int> roots(sz + 1);
    roots[sz] = 1;
    //dsu.view();
    for (int i = sz-1; i >= 0; i--) {
        roots[i] = roots[i+1];
        for (auto [x,y]:evs[i]) {
            roots[i] = dsu.join(roots[i], x,y);
        }
        //dsu.view();
    }
//dbg(roots);

    int las = 0;
    int q, K, S;
    //cin >> q >> K >> S;
    q=in(),K=in(),S=in();
    while (q--) {
        int x, h;
        //cin >> x >> h;
        x=in(),h=in();
        x = (0ll+x + K*las - 1) % n;
        h = (0ll+h + K*las) % (S+1);
        h = pos(h+1);
        //cerr<<":"<<h<<endl;
        las = dsu.ans(roots[h], x);
        //cout << las << "\n";
        printf("%d\n", las);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int T; T=in();//cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
