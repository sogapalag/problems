#include <bits/stdc++.h>

using namespace std;

typedef struct SplayNode* sn;

struct SplayNode {
    int id;
    sn pa, ch[2];

    SplayNode(int _id) : id(_id) {
        pa = ch[0] = ch[1] = NULL;
    }
    inline int is_snd() {
        if (!pa) return -1;
        return pa->ch[1] == this;
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
    }
    inline void splay() {
        while (!is_root()) {
            if (!pa->is_root()) is_snd() == pa->is_snd() ? pa->rot() : rot();
            rot();
        }
    }
};
