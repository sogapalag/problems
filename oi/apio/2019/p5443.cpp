#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    using pi=pair<int, int>;
    int n;
    vector<int> p;
    vector<int> r;
    vector<pi> histo;

    Dsu(int _n) : n(_n)
        , p(n)
        , r(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) { // don't compress path
        while (x != p[x]) x = p[x];
        return x;
        //return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (r[x] < r[y]) swap(x, y);
        histo.emplace_back(x, y);
        p[y] = x; r[x] += r[y];
        return 1;
    }
    inline int join(pi e) {
        return join(e.first, e.second);
    }
    int size(int x) {
        return r[find(x)];
    } 
    void roll_back() {
        int x,y;
        tie(x,y) = histo.back(); histo.pop_back();
        r[x] -= r[y]; p[y] = y;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline bool check(pi e) {
        return check(e.first, e.second);
    }
};
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};
struct Event {
    int i, t, w;
    Event() {}
    Event(int _i, int _t, int _w) : i(_i), t(_t), w(_w) {}
    bool operator<(const Event& _oth) const {
        return w > _oth.w;
    }
};
const int N = 100005; 
int id[N], now[N];
bool trk[N];
int id1[N], id2[N]; 

// method: sqrt
// for each block: ensure qrs sort by w
//   untrk: ensure sort by w, (thus two-pointer add) no need roll_back
//   trk: for each cell, simulate(time) now weight end with t. join >=w, calc, then roll_back
void solve() {
    int n,m;
    cin >> n >> m;
    vector<Edge> es(m);
    for (auto& e: es) {
        cin >> e.u >> e.v >> e.w;
        --e.u; --e.v;
    }
    int q; cin >> q;
    const int BLOCK_SIZE = max(256, min(1024, (int)(0.2*(n+q+m)))); 
    vector<int> res(q + 1);
    vector<Event> evs, qrs;
    // 86pts
    //auto __calc = [&](){
    //    vector<int> id(m);
    //    iota(id.begin(), id.end(), 0);
    //    sort(id.begin(), id.end(), [&](auto& u, auto& v){
    //        return es[u].w > es[v].w;
    //    });
    //    sort(qrs.begin(), qrs.end());
    //    vector<bool> trk(m);
    //    vector<int> now(m);
    //    auto a = evs;
    //    for (auto& [i,t,w]:a) {
    //        trk[i] = true;
    //        t = 0; // past
    //        w = es[i].w; // past
    //    }
    //    Dsu d(n);
    //    auto i = id.begin();
    //    for (auto [_,t,w]: qrs) {
    //        while (i != id.end() && es[*i].w >= w) {
    //            if (!trk[*i]) d.join(es[*i].u, es[*i].v);
    //            ++i;
    //        }
    //        for (auto [ii,tt,ww]: a) if (tt <= t) now[ii] = ww;
    //        for (auto [ii,tt,ww]: evs) if (tt <= t) now[ii] = ww;
    //        int did = 0;
    //        for (auto [ii,_t,_w]: evs) if (now[ii] >= w) {
    //            did += d.join(es[ii].u, es[ii].v);
    //        }
    //        res[t] = d.size(_);
    //        while (did--) d.roll_back();
    //    }
    //    for (auto [i,_t,w]: evs) es[i].w = w;
    //    evs.clear(); qrs.clear();
    //};
    auto comp = [&](auto& u, auto& v){
        return es[u].w > es[v].w;
    };
    // AC with some log optimization
    auto calc = [&](){
        sort(qrs.begin(), qrs.end());
        int end1 = 0, end2 = 0;
        for (auto [i,_t,_w]:evs)if(!trk[i]) { // id2.. duped.
            trk[i] = true;
            id2[end2++] = i; 
        }
        for (int _ = 0; _ < m; _++) {
            if (!trk[id[_]]) {
                id1[end1++] = id[_];
            }
        }
        Dsu d(n);
        int* i = &id1[0];
        for (auto [_,t,w]: qrs) {
            while (i != id1+end1 && es[*i].w >= w) {
                d.join(es[*i].u, es[*i].v);
                ++i;
            }
            //for (auto [ii,tt,ww]: evs) now[ii] = es[ii].w;
            for (int* ii = &id2[0]; ii != id2+end2; ++ii) now[*ii] = es[*ii].w;
            for (auto [ii,tt,ww]: evs) if (tt <= t) now[ii] = ww;
            int did = 0;
            //for (auto [ii,_t,_w]: evs) if (now[ii] >= w) {
            //    did += d.join(es[ii].u, es[ii].v);
            //}
            for (int* ii = &id2[0]; ii != id2+end2; ++ii) if(now[*ii] >= w) {
                did += d.join(es[*ii].u, es[*ii].v);
            }
            res[t] = d.size(_);
            while (did--) d.roll_back();
        }
        for (auto [i,_t,w]: evs) es[i].w = w, trk[i]=0, now[i]=0;
        // key optimization, merge sort
        swap(id, id1);
        sort(id2, id2+end2, comp);
        memcpy(id+end1, id2, 4*end2);
        inplace_merge(id, id+end1, id+m, comp);
        evs.clear(); qrs.clear();
    };
    iota(id, id+m, 0);
    sort(id, id+m, comp);
    for (int t = 1; t <= q; t++) {
        int op,i,w;
        cin >> op >> i >> w;
        i--;
        if (op == 1) evs.emplace_back(i, t, w);
        else qrs.emplace_back(i, t, w);
        if (t % BLOCK_SIZE == 0) {
            calc();
        }
    }
    if (qrs.size()) calc();
    for (int x: res)if(x)cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
