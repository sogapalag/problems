#include <bits/stdc++.h>

using namespace std;

struct Bip {
    int n,m; // #l, #r
    vector<vector<int>> g;
    vector<int> left;
    vector<bool> trk;

    Bip() {}
    Bip(int _n) : n(_n), m(_n) {
        init();
    }
    Bip(int _n, int _m) : n(_n), m(_m) {
        init();
    }
    void init() {
        g.resize(n);
        left.assign(m, -1);
        trk.assign(n, false);
    }
    inline void add(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 <= r && r < m);
        g[l].emplace_back(r);
    }

    bool dfs(int l) {
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    }
    int match() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        return cnt;
    }
};

using u64=unsigned long long ;

u64 mod_mul(u64 x, u64 y, u64 m) {
    if (__builtin_clzll(x)+__builtin_clzll(y) >= 64) {
        x *= y;
        return (x>=m? x%m : x);
    } else {
        return (__uint128_t)x*y %m;
    }
}

u64 mod_pow(u64 x, u64 e, u64 m) {
    u64 res = 1;
    for (; e; e >>= 1) {
        if (e & 1) res = mod_mul(res, x, m);
        x = mod_mul(x, x, m);
    }
    return res;
}

// [0, 2^32) 0.2 sec / 10^6.
// [0, 2^64) 1.3 sec / 10^6
// pass u32/u64 plz, avoid potential negative.
bool miller_rabin(u64 p) {
    static pair<u64, valarray<u64>> WIT[] = {
        {2'046, {2}},
        {1'373'652, {2, 3}},
        {9'080'190, {31, 73}},
        {25'326'000, {2, 3, 5}},
        {4'759'123'140, {2, 7, 61}},
        {1'112'004'669'632, {2, 13, 23, 1662803}},
        {2'152'302'898'746, {2, 3, 5, 7, 11}},
        {3'474'749'660'382, {2, 3, 5, 7, 11, 13}},
        {341'550'071'728'320, {2, 3, 5, 7, 11, 13, 17}},
        {0xFFFF'FFFF'FFFF'FFFF, {2, 3, 5, 7, 11, 13, 17, 19, 23}}};

    if (p%2 == 0) return p==2;
    if (p == 1) return false;
    u64 d = p - 1, e = 0;
    while (d%2 == 0) d/=2, e++;
    int _k = 0;
    while (WIT[_k].first < p) _k++;
    for (const auto& a: WIT[_k].second) {
        u64 t = mod_pow(a, d, p);
        if (t == 1 || t == p-1) continue;
        bool ok = false;
        for (size_t _ = 0; _ < e; _++) {
            t = mod_mul(t, t, p);
            if (t == 1) return false;
            if (t == p-1) {ok=true; break;}
        }
        if (ok) continue;
        else return false;
    }
    return true;
}

// transform to bar, adj-differ in this pos.
// since operation is flip two bars , x, x+p.
// consider pair i,j
// three situation
//    d: odd-prime,  cost = 1
//    d: odd-compo,  cost = 3   // any two odd-prime abs even, so 2+1
//    d: even,       cost = 2
// let k, be #cost=1. f(k)-> as k->. so Bip
void solve() {
    int n; cin >> n;
    set<int> bar;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (bar.find(x) == bar.end())
            bar.insert(x);
        else bar.erase(x);

        if (bar.find(x+1) == bar.end())
            bar.insert(x+1);
        else bar.erase(x+1);
    }
    vector<int> a[2];
assert(bar.size()%2 == 0);
    for (auto& x: bar) {
        a[x&1].emplace_back(x);
    }

    n = a[0].size();
    int m = a[1].size();
    Bip g(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            u64 d = abs(a[0][i] - a[1][j]);
            if (d <= 2) continue;
            if (miller_rabin(d))
                g.add(i, j);
        }
    }
    int k = g.match();

    int res = k + ((n-k)/2 + (m-k)/2) * 2 + ((m-k)&1)*3;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
