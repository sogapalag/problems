#include <bits/stdc++.h>

using namespace std;

// a subtree size LCT
// sz, subtree size; lt, light/virtual, aka not in splay but still sub. lt2=sum lt^2
// passed cf 1172e

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
