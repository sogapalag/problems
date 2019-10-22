#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START slider
// slider of [l,r) r-l=d range min/max
// in begin/end, r-l could < d
template <typename T=int>
struct Slider {
    vector<T> a;
    int n, d;
    deque<int> mi, mx;

    vector<int> lid, hid;

    Slider(vector<T> _a, int _d) : a(_a), d(_d) {
        n = a.size();
        lid.resize(n + d);
        hid.resize(n + d);
        build();
    }
    void build() {
        for (int i = 0; i < n+d-1; i++) {
            while (i < n && !mi.empty() && a[mi.back()] >= a[i]) {
                mi.pop_back();
            }
            mi.push_back(i);
            lid[i+1] = mi.front();
            if (i-d+1 >= 0 && i-d+1 == mi.front()) {
                mi.pop_front();
            }

            while (i < n && !mx.empty() && a[mx.back()] <= a[i]) {
                mx.pop_back();
            }
            mx.push_back(i);
            hid[i+1] = mx.front();
            if (i-d+1 >= 0 && i-d+1 == mx.front()) {
                mx.pop_front();
            }
        }
    }
    
    // [l, r)
    int min_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? lid[r] : lid[l+d];
    }
    T get_min(int l, int r) {
        return a[min_id(l,r)];
    }
    int max_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? hid[r] : hid[l+d];
    }
    T get_max(int l, int r) {
        return a[max_id(l,r)];
    }
};
// SNIPPETS_END
