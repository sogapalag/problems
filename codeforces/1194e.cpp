#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

struct Vine {
    int x, yl, yr;
    Vine() {}
    Vine(int _x, int _yl, int _yr) : x(_x), yl(_yl), yr(_yr) {}
};
struct Hint {
    int x, y;
    bool l;
    Hint() {}
    Hint(int _x, int _y, bool _l): x(_x), y(_y), l(_l) {}
};

const int N = 5003; 
// sort V(line) by x, sort (split H, to '(', ')' ) by x. 
// then linear sweep, for fixed V[i], <=x H add-in
// then for each V[j], check any H need modify.
// then range num, C(num,2)
void solve() {
    int n; cin >> n;
    vector<Vine> V;
    vector<Hint> H;
    for (int _ = 0; _ < n; _++) {
        int x,y, u,v;
        cin >> x >> y >> u >> v;
        x += N; y += N; u += N; v += N;
        if (x > u) swap(x, u);
        if (y > v) swap(y, v);
        if (x == u) {
            V.emplace_back(x, y, v);
        }else{
            assert(y==v);
            H.emplace_back(x, y, 1);
            H.emplace_back(u, y, 0);
        }
    }
    sort(V.begin(), V.end(), [&](auto& u, auto& v){
            return u.x < v.x;
            });
    sort(H.begin(), H.end(), [&](auto& u, auto& v){
            return u.x < v.x;
            });
    n = V.size();
    int m = H.size();
    long long res = 0;
    for (int i = 0; i < n; i++) {
        Fenwick<int> Y(10'011);
        int k = 0;
        while (k < m && H[k].x <= V[i].x) {
            Y.add(H[k].y, H[k].l? +1: -1);
            k++;
        }
        for (int j = i+1; j < n; j++) {
            while (k < m && H[k].x < V[j].x) {
                if (!H[k].l && Y.query(H[k].y, H[k].y) == 1)
                    Y.add(H[k].y, -1);
                k++;
            }
            int l = max(V[i].yl, V[j].yl);
            int r = min(V[i].yr, V[j].yr);
            if (l < r) {
                int num = Y.query(l, r);
                res += num*(num-1)/2;
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
