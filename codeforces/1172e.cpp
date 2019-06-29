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
        //dbg(u->id); dbg(v->id); dbg(v->pa->id);
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


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<array<int,3>>> mod(n+1);
    vector<vector<int>> g(n+1);
    vector<int> c(n+1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        c[i] = x;
        mod[x].push_back({0, 1, i});
    }
    g[0].emplace_back(1);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    for (int i = 1; i <= m; i++) {
        int u, x; cin >> u >> x;
        if (c[u] == x) continue;
        mod[c[u]].push_back({i, 0, u});
        c[u] = x;
        mod[x].push_back({i, 1, u});
    }
    vector<int> p(n+1, -1);
    function<void(int)> dfs = [&](int u) {
        for (auto& v: g[u]) {
            if (!~p[v]) {
                p[v] = u;
                dfs(v);
            }
        }
    };
    dfs(0);
    //dbg(p);
    LCT t(n+1);
    for (int i = 1; i <= n; i++) {
        t.link(p[i], i);
    }
    const long long TOT = (long long)n*n;
    assert(t.tot == TOT);
    vector<long long> de(m+1, 0);
    for (int x = 1; x <= n; x++) {
        long long tmp = TOT;
        for (auto& w: mod[x]) {
            //dbg(w);
            if (w[0] == 0) {
                t.cut(p[w[2]], w[2]); tmp = t.tot;
            } else {
                de[w[0]] -= t.tot;
                if (w[1] == 1) {
                    t.cut(p[w[2]], w[2]);
                } else {
                    t.link(p[w[2]], w[2]);
                }
                de[w[0]] += t.tot;
            }
        }
        //dbg(de[1]);
        de[0] += tmp;
        int sz = mod[x].size();
        for (int i = sz-1; i >= 0; i--) {
            auto& w = mod[x][i];
            if (w[1] == 1) {
                t.link(p[w[2]], w[2]);
            } else {
                t.cut(p[w[2]], w[2]);
            }
        }
        assert(t.tot == TOT);
    }
    for (int i = 0; i < m; i++) {
        de[i+1] += de[i];
    }
    long long TTT = (long long)n*n*n;
    for (auto& x: de) {
        cout << (TTT - x) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
