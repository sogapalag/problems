#include <bits/stdc++.h>

using namespace std;

struct Sieve {
    int sz;
    vector<bool> is;
    vector<int> prime;
    Sieve(int n = 45000):sz(n) {
        prime.reserve(n/6);
        is.assign(n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; (int64_t)p*p <= n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    }
    // x=p0^e0 * p1^e1 *...
    vector<pair<int, int>> factor(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        vector<pair<int, int>> res;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
            if (x % p == 0) {
                int e = 0;
                while (x % p == 0) {
                    e++; x /= p;
                }
                res.emplace_back(p, e);
            }
        }
        if (x != 1)
            res.emplace_back(x, 1);
        return res;
    }
    // divisors
    vector<int> divs(int x, bool sorted=false) {
        vector<int> res;
        res.emplace_back(1);
        for (auto& p: factor(x)) {
            int b, e;
            tie(b, e) = p;
            int sz = res.size();
            int y = 1;
            while (e--) {
                y *= b;
                for (int i = 0; i < sz; i++) {
                    res.emplace_back(res[i] * y);
                }
            }
        }
        if (sorted) sort(res.begin(), res.end());
        return res;
    }
    // number of divisors
    int num_divs(int x) {
        int res = 1;
        for (auto& pe: factor(x)) {
            res *= (1+pe.second);
        }
        return res;
    }
    // simple prime test
    bool is_prime(int x) {
        if (x <= sz) return is[x];
        return factor(x)[0].first == x;
    }
    // prime divisors
    vector<int> p_divs(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        vector<int> res;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
            if (x % p == 0) {
                while (x % p == 0) {
                    x /= p;
                }
                res.emplace_back(p);
            }
        }
        if (x != 1)
            res.emplace_back(x);
        return res;
    }
    // Hint: if query many times, a slight fast formula by mobius: res = sum_{d|c} mu[d] * (m/d)
    // count [1..=m] coprime to c
    int coprime(int m, int c){
        int tmp = 0;
        auto di = p_divs(c);
        int sz = di.size();
        for (int msk = 1; msk < (1<<sz); msk++) {
            int prod = 1;
            for (int k = 0; k < sz; k++) {
                if (msk & (1<<k)) {
                    prod *= di[k];
                }
            }
            int sign = (__builtin_popcount(msk)&1)? 1: -1;
            tmp += sign * m/prod;
        }
        return m - tmp;
    };
    // euler phi, [1..=x] coprime to x
    int phi(int x) {
        assert(x > 0);
        if (x == 1) return 1;
        int res = x;
        for (auto& p: p_divs(x)) {
            (res/=p)*=(p-1);
        }
        return res;
    }
    // pre-comp phi table
    vector<int> phi_table(int n) {
        assert(sz >= n);
        vector<int> res(n+1);
        iota(res.begin(), res.end(), 0);
        for (const int& p: prime) {
            if (p > n) break;
            --res[p];
            for (int i = 2*p; i <= n; i += p)
                (res[i]/=p)*=p-1;
        }
        return res;
    }
    // mobius, (-1)^k; 0, p^2|x
    int8_t mu(int x) {
        assert(x > 0 && (int64_t)sz*sz >= x);
        if (x == 1) return 1;
        int cnt = 0;
        for (const int& p: prime) {
            if ((int64_t)p*p > x) break;
            if (x % p == 0) {
                cnt++; x /= p;
            }
            if (x % p == 0) {
                return 0;
            }
        }
        if (x != 1) cnt++;
        return (cnt&1)?-1:1;
    }
    // pre-comp mobius table
    vector<int8_t> mobius_table(int n) {
        assert(sz >= n);
        vector<int8_t> res(n+1, 1);
        for (int i = 2; i <= n; i++) {
            if (is[i]) res[i] = -1;
            for (const int& p: prime) {
                if (p > i || (int64_t)p*i > n) break;
                if (i % p == 0) {
                    res[i*p] = 0;
                } else {
                    res[i*p] = -res[i];
                }
            }
        }
        return res;
    }
}s(1e6+10);
const int N = 1e6+10; 
int pos[N];

void solve() {
    int n; cin >> n;
    vector<int> a;
    vector<pair<int, int>> es;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x == 1) {
            cout << 1; return;
        }
        vector<int> ps;
        for (auto& _: s.factor(x)) {
            if (_.second&1) ps.push_back(_.first);
        }
        if(ps.empty()) {
            cout << 1; return;
        }
        if (ps.size() == 1) a.push_back(ps[0]);
        else {
            es.emplace_back(ps[0], ps[1]);
        }
    }
    n = a.size();
    int m = es.size();
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    if ((int)a.size() < n) {
        cout << 2; return;
    }
    sort(es.begin(), es.end());
    es.erase(unique(es.begin(), es.end()), es.end());
    if ((int)es.size() < m) {
        cout << 2; return;
    }

    auto ps = a;
    for (auto& _: es) {
        ps.emplace_back(_.first);
        ps.emplace_back(_.second);
    }
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    for (int i = 0; i < (int)ps.size(); i++) {
        pos[ps[i]] = i;
    }
    for (auto& x: a) {
        x = pos[x];
    }
    for (auto& _: es) {
        _.first = pos[_.first];
        _.second = pos[_.second];
    }

    vector<vector<int>> g(ps.size());
    vector<int> d(ps.size());
    for (auto& _: es) {
        int x,y;
        tie(x,y)= _;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int res = 1e9;
    //auto bfs = [&](int x, int y){
    //    fill(d.begin(), d.end(), -1);
    //    d[x] = 0;
    //    queue<int> q; q.push(x);
    //    while (!q.empty()) {
    //        int u = q.front(); q.pop();
    //        for (int v:g[u])if(!(u==x&&v==y)){
    //            if (d[v]==-1){
    //                d[v] = d[u]+1;
    //                if (v == y) return d[v];
    //                q.push(v);
    //            }
    //        }
    //    }
    //    return -1;
    //};
    //for (auto& _: es) {
    //    int x,y;
    //    tie(x,y) = _;
    //    int dis = bfs(x,y);
    //    if (dis!=-1) res = min(res, dis+1);
    //}

    vector<bool> good(ps.size());
    for (auto& x: a) {
        good[x] = true;
    }
    //auto bfs2 = [&](int x){
    //    fill(d.begin(), d.end(), -1);
    //    d[x] = 0;
    //    queue<int> q; q.push(x);
    //    while (!q.empty()) {
    //        int u = q.front(); q.pop();
    //        for (int v:g[u])if(d[v]==-1){
    //            d[v] = d[u]+1;
    //            if (good[v]) return d[v];
    //            q.push(v);
    //        }
    //    }
    //    return -1;
    //};
    //for (auto& x: a) {
    //    int dis = bfs2(x);
    //    if (dis!=-1) res = min(res, dis+2);
    //}


    // key optim: each edge at least one <= 1000, since x*x <=1e6
    int LIM = 0;
    for (auto& x: ps) {
        if (x < 1000) LIM = pos[x];
    }
    cerr<<LIM<<endl;

    // good can omit, create dummy node connect to it, then check bfs(dummy)
    auto bfs = [&](int s){
        fill(d.begin(), d.end(), -1);
        vector<int> pa(ps.size(), -1);
        d[s] = 0;
        queue<int> q; q.push(s);
        int mi[2] = {1<<29, 1<<29};
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (good[u]) {
                mi[1] = min(mi[1], d[u]);
                if (mi[1] < mi[0]) swap(mi[0], mi[1]);
            }
            for (int v:g[u])if(v != pa[u]){
                if (d[v] == -1) {
                    pa[v] = u;
                    d[v] = d[u] + 1;
                    q.push(v);
                } else {
                    res = min(res, d[v] + d[u] + 1);
                }
            }
        }
        res = min(res, mi[0] + mi[1] + 2);
    };
    for (int i = 0; i <= LIM; i++) {
        bfs(i);
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
