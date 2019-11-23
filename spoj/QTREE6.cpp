#include <bits/stdc++.h>

using namespace std;

typedef struct SplayNode* sn;

struct SplayNode {
    int id;
    sn pa, ch[2];
    int sz, lt;
    long long lt2;

    SplayNode(int _id) : id(_id) {
        pa = ch[0] = ch[1] = NULL;
        sz = 1; lt = 0; lt2 = 0;
    }
    inline void upd() {
        sz = 1 + lt + (ch[0]?ch[0]->sz:0) + (ch[1]?ch[1]->sz:0);
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

    LCT(int _n) : n(_n), tot(0) {
        s.resize(n);
        for (int i = 0; i < n; i++) {
            s[i] = new SplayNode(i);
        }
    }
    inline void access(sn v) {
        assert(v);
        for (sn y = NULL, x = v; x; y = x, x = x->pa) {
            x->splay();
            // info
            int tmp = x->ch[1]?x->ch[1]->sz:0;
            x->lt += tmp; x->lt2 += (long long)tmp*tmp;
            tmp = y?y->sz:0;
            x->lt -= tmp; x->lt2 -= (long long)tmp*tmp;
            // info
            x->ch[1] = y;
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
    inline long long get_lt2(sn v) {
        sn r = find_root(v);
        access(r);
        return r->lt2;
    }
    // make sure u->v a graph edge
    // link the light
    inline void _link(sn u, sn v) {
        assert(u); assert(v); assert(u!=v);
        tot -= get_lt2(u) + get_lt2(v);
        access(u);
        access(v);
        assert(!v->pa);
        v->pa = u;
        u->lt += v->sz; u->lt2 += (long long)v->sz * v->sz;
        u->upd();
        tot += get_lt2(u);
    }
    // make light then remove
    inline void _cut(sn u, sn v) {
        assert(u); assert(v); assert(u!=v);
        tot -= get_lt2(v);
        access(v);
        access(u);
        assert(v->pa == u);
        v->pa = NULL;
        u->lt -= v->sz; u->lt2 -= (long long)v->sz * v->sz;
        u->upd();
        tot += get_lt2(u) + get_lt2(v);
    }
    inline void link(int u, int v) {
        _link(s[u], s[v]);
    }
    inline void cut(int u, int v) {
        _cut(s[u], s[v]);
    }
};


// two lct, u->v exist c iff co[v] = c
// so for query u, belong to lct[co[u]], the up path must exist by above, except for r=find_root(u)
void solve() {
    int n; cin >> n;
    LCT lct[2]{n,n};
    // why vector<LCT> init dup?
    vector<vector<int>> g(n);
    vector<int> pa(n, -1), co(n, 1);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    //cout << lct[0].s[0]->sz << "?\n";
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p){
            lct[1].link(u, v);
            pa[v] = u;
            dfs(v,u);
        }
    };
    dfs(0, -1);

    //cout << lct[0].s[0]->sz << "?\n";
    int q; cin >> q;
    while (q--) {
        int op, u;
        cin >> op >> u; u--;
        if (op == 1) {
            if (pa[u] == -1) {co[u]^=1;continue;}
            lct[co[u]].cut(pa[u], u);
            co[u] ^= 1;
            lct[co[u]].link(pa[u], u);
        } else {
            //cout << (co[u]?1:0) << "\n";
            auto U = lct[co[u]].s[u];
            auto R = lct[co[u]].find_root(U);
            int r = R->id;
            //cout << r << "\n";
            if (co[r] != co[u]) {
                R = R->ch[1];
                assert(co[R->id] == co[u]);
            }
            cout << R->sz << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
