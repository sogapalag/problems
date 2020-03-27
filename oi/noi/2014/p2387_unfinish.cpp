#include <bits/stdc++.h>

using namespace std;

typedef struct SplayNode* sn;

struct SplayNode {
    int id;
    sn pa, ch[2];
    //int sz, lt;
    //long long lt2;

    int w;
    sn mx;
    bool rev;


    //SplayNode(int _id) : id(_id) {
    //    pa = ch[0] = ch[1] = NULL;
    //    //sz = 1; lt = 0; lt2 = 0;
    //}
    SplayNode(int _id, int _w) : id(_id), w(_w) {
        pa = ch[0] = ch[1] = nullptr;
        mx = this;
        rev = false;
    }
    inline void upd() {
        //sz = 1 + lt + (ch[0]?ch[0]->sz:0) + (ch[1]?ch[1]->sz:0);
        mx = this;
        if (ch[0] && ch[0]->mx->w > mx->w) mx = ch[0]->mx;
        if (ch[1] && ch[1]->mx->w > mx->w) mx = ch[1]->mx;
    }
    inline int is_snd() {
        if (!pa) return -1;
        if (pa->ch[0] == this) return 0;
        if (pa->ch[1] == this) return 1;
        return -2; // ppp
    }
    inline bool is_root() {
        return is_snd() < 0;
    }
    inline friend void set_link(sn _pa, sn _ch, int _di) {
        if (_ch) _ch->pa = _pa;
        if (_di >= 0) _pa->ch[_di] = _ch;
    }
    inline void rot() {
        assert(!is_root());
        int di = is_snd();
        sn tp = pa;
        set_link(tp->pa, this, tp->is_snd());
        set_link(tp, ch[di^1], di);
        set_link(this, tp, di^1);
        tp->upd();
        upd();
    }
    inline void splay() {
        while (!is_root()) {
            if (!pa->is_root()) is_snd() == pa->is_snd() ? pa->rot() : rot();
            rot();
        }
    }
};

struct LCT {
    int n;
    long long tot;
    vector<sn> s;
    vector<sn> stk; //
    //LCT(int _n) : n(_n), tot(0) {
    //    s.resize(n);
    //    for (int i = 0; i < n; i++) {
    //        //s[i] = new SplayNode(i);
    //    }
    //}
    LCT(vector<int>& a) {
        n = a.size();
        s.resize(n);
        for (int i = 0; i < n; i++) {
            s[i] = new SplayNode(i, a[i]);
        }
    }
    inline void access(sn v) {
        assert(v);
        stk.push_back(v);
        for (sn x = v; !x->is_root(); x = x->pa) stk.push_back(x->pa);
        while (!stk.empty()) {
            push_down(stk.back()); stk.pop_back();
        }
        for (sn y = NULL, x = v; x; y = x, x = x->pa) {
            x->splay();
            // info
            //int tmp = x->ch[1]?x->ch[1]->sz:0;
            //x->lt += tmp; x->lt2 += (long long)tmp*tmp;
            //tmp = y?y->sz:0;
            //x->lt -= tmp; x->lt2 -= (long long)tmp*tmp;
            // info
            x->ch[1] = y;
            //
            x->upd();
        }
        v->splay();
    }
    // graph root
    inline sn find_root(sn v) {
        assert(v);
        access(v);
        while (v->ch[0]) {
            v = v->ch[0];
        }
        v->splay();
        return v;
    }
    //inline long long get_lt2(sn v) {
    //    sn r = find_root(v);
    //    access(r);
    //    return r->lt2;
    //}
    // make sure u->v a graph edge
    // link the light
    inline void _link(sn u, sn v) {
        assert(u); assert(v); assert(u!=v);
        //tot -= get_lt2(u) + get_lt2(v);
        access(u);
        access(v);
        assert(!v->pa);
        v->pa = u;
        //u->lt += v->sz; u->lt2 += (long long)v->sz * v->sz;
        u->upd();
        //tot += get_lt2(u);
    }
    // make light then remove
    inline void _cut(sn u, sn v) {
        assert(u); assert(v); assert(u!=v);
        //tot -= get_lt2(v);
        access(v);
        access(u);
        assert(v->pa == u);
        v->pa = NULL;
        //u->lt -= v->sz; u->lt2 -= (long long)v->sz * v->sz;
        u->upd();
        //tot += get_lt2(u) + get_lt2(v);
    }
    inline void link(int u, int v) {
        _link(s[u], s[v]);
    }
    inline void cut(int u, int v) {
        _cut(s[u], s[v]);
    }

    void push_down(sn v) {
        if (v->rev) {
            swap(v->ch[0], v->ch[1]); v->rev = 0;
            if (v->ch[0]) v->ch[0]->rev^=1;
            if (v->ch[1]) v->ch[1]->rev^=1;
        }
    }
    void make_root(sn v) {
        access(v); v->splay(); v->rev^=1;
    }
    void _LINK(sn u, sn v) {
        make_root(v);
        v->pa = u;
        u->upd();
    }
    void _CUT(sn u, sn v) {
        make_root(u);
        access(v);
        v->splay();
        v->pa = v->ch[0] = nullptr;
    }
    sn _query(sn u, sn v) {
        make_root(u);
        access(v);
        v->splay();
        return v->mx;
    }
    void LINK(int u, int v) {
        _LINK(s[u], s[v]);
    }
    void CUT(int u, int v) {
        _CUT(s[u], s[v]);
    }
    sn query(int u, int v) {
        return _query(s[u], s[v]);
    }
};
struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) : n(_n)
        , p(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> es(m);
    for (int _ = 0; _ < m; _++) {
        int x,y, a,b;
        cin >> x >> y >> a >> b;
        x--;y--;
        es[_] = {x,y,a,b};
    }
    sort(es.begin(), es.end(), [&](auto& u, auto& v){
        return get<2>(u) < get<2>(v);
    });
    vector<int> a(n + m);
    for (int i = 0; i < m; i++) {
        a[n + i] = get<3>(es[i]);
    }

    LCT lct(a);
    Dsu d(n);
    int res = 1e9;
    for (int i = 0; i < m; i++) {
        int u,v,w0,w1;
        tie(u,v,w0,w1) = es[i];
        if (d.check(u, v)) {
            auto e = lct.query(u, v);
            if (e->w <= w1) continue;
            int x,y,__,___;
            tie(x,y,__,___) = es[e->id - n];
            lct.CUT(x, e->id);
            lct.CUT(y, e->id);
        } else {
            d.join(u, v);
        }
        lct.LINK(u, n+i);
        lct.LINK(v, n+i);
        if (!d.check(0,n-1)) continue;
        res = min(res, w0 + lct.query(0, n-1)->w);
    }
    if (res > 1e8) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
