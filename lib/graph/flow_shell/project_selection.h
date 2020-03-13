#include "../dinic.h"

struct ProjectSelection {
    int n;
    int s,t;
    Dinic mc;
    using F = Dinic::F;
    F positive;

    ProjectSelection(int _n) : n(_n)
        , s(n)
        , t(n+1)
        , mc(n+2, s, t)
        , positive(0)
    {}

    // i: [0..n)
    void add_proj(int i, F profit) {
        if (profit >= 0) {
            mc.add(s, i, profit);
            positive += profit;
        } else {
            mc.add(i, t, -profit);
        }
    }

    // u dep on v: [0..n)
    // i.e. u implies v
    void add_dep(int u, int v) {
        mc.add(u, v);
    }

    F profit() {
        return positive - mc.flow();
    }
    // A\{s} := s_achivable
    bool chosen(int i) const {
        return mc.d[i] != -1;
    }
};

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

// used for most projects without deps. need to shrink
struct ProjectSelectionDumper {
    using F = Dinic::F;
    F sum;

    ProjectSelectionDumper(const vector<F>& profits, const vector<pair<int, int>>& deps) {
        vector<bool> trk(profits.size(), false);
        Compress<int> c;
        for (auto& p: deps) {
            c.get_id(p.first);
            c.get_id(p.second);
            trk[p.first] = true;
            trk[p.second] = true;
        }
        
        ProjectSelection ps(c.num.size());
        sum = 0;
        // must choose profit > 0 without deps
        for (int i = 0; i < (int)profits.size(); i++) {
            if (trk[i]) {
                ps.add_proj(c.get_id(i), profits[i]);
            } else if (profits[i] > 0) {
                sum += profits[i];
            }
        }
        for (auto& p: deps) {
            int u = c.get_id(p.first);
            int v = c.get_id(p.second);
            ps.add_dep(u, v);
        }
        sum += ps.profit(); 
    }
};
