#include <bits/stdc++.h>

using namespace std;

struct RangeAddGlobalMax {
    using T = int;
    int N;
    vector<T> a, d;

    RangeAddGlobalMax(int n, T leaf_default = 0) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    RangeAddGlobalMax(const vector<T>& leaves) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N <<= 1;
        a.assign(N<<1, 0xafafafaf);
        d.assign(N, 0);
    }
    inline void pull(int i) {
        a[i] = max(a[i<<1], a[i<<1|1]);
    }
    void build() {
        for (int i = N-1; i >= 1; i--) pull(i);
    }
    inline void apply(int i, const T& val) {
        a[i] += val;
        if (i < N) d[i] += val;
    }
    inline void push(int i) {
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = 0;
    }
    void add(int l, int r, const T& val, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        if (l <= sl && sr <= r) return apply(i, val);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        add(l, r, val, il, sl, sm);
        add(l, r, val, ir, sm, sr);
        pull(i);
    }

    void add(int l, int r, const T& val) {
        add(l, r, val, 1, 0, N);
    }
    T get_max() const {
        return a[1];
    }
};
struct MaxRectangleCover {
    using X = int;
    struct Event {
        X x; int yl, yr;
        int val;
        Event() {}
        Event(X _x, int _yl, int _yr, int _val) : x(_x), yl(_yl), yr(_yr), val(_val) {}
        bool operator<(const Event& _oth) const {
            return x < _oth.x;
        }
    };
    vector<Event> evs;
    int min_y, max_y;
    MaxRectangleCover() : min_y(1e8), max_y(-1) {}

    void add_rect(X xl, int yl, X xr, int yr) {
        min_y = min(min_y, yl);
        max_y = max(max_y, yr);
        evs.emplace_back(xl, yl, yr, +1);
        evs.emplace_back(xr, yl, yr, -1);
    }

    int solve() {
        assert(0 <= min_y && min_y < max_y && max_y <= 1000006);// set limit
        sort(evs.begin(), evs.end());
        RangeAddGlobalMax s(max_y);
        int res = 0;
        int n = evs.size();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && evs[j].x == evs[i].x) {
                s.add(evs[j].yl, evs[j].yr, evs[j].val);
                j++;
            }
            res = max(res, s.get_max());
            i = j;
        }
        return res;
    }
};

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};
void solve() {
    int n, R;
    cin >> n >> R;
    vector<pair<int, int>> a(n);
    vector<int> Ys;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x+y, x-y};
        Ys.emplace_back(x-y);
        Ys.emplace_back(x-y + 2*R+1);
    }
    Compress<int> cy(Ys);
    MaxRectangleCover mrc;
    for (int i = 0; i < n; i++) {
        int x,y;
        tie(x,y) = a[i];
        mrc.add_rect(x, cy.get_id(y), x+2*R+1, cy.get_id(y+2*R+1));
    }
    cout << mrc.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
