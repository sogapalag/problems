#include <bits/stdc++.h>

using namespace std;


struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

struct Node {
    int x, y, id;
    Node(): x(0), y(0), id(-1) {}
    Node(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}
};
const int N = 100005; 
set<int> X[N], Y[N];

// points with same x or y, will finally connect a complete grid
void solve() {
    int n; cin >> n;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y, i};
    }
    Dsu d(n);
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.x < v.x;
            });
    int i = 0;
    while (i < n) {
        int j = i+1;
        while (j < n && a[j].x == a[i].x) {
            d.join(a[i].id, a[j].id);
            j++;
        }
        i = j;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.y < v.y;
            });
    i = 0;
    while (i < n) {
        int j = i+1;
        while (j < n && a[j].y == a[i].y) {
            d.join(a[i].id, a[j].id);
            j++;
        }
        i = j;
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.id < v.id;
            });
    for (int i = 0; i < n; i++) {
        int k = d.find(i);
        X[k].insert(a[i].x);
        Y[k].insert(a[i].y);
    }
    long long res = 0;
    for (int k = 0; k < n; k++) {
        int szx = X[k].size();
        int szy = Y[k].size();
        if (szx > 1 && szy > 1) {// form grid
            res += 1ll*szx*szy - d.r[k];
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
