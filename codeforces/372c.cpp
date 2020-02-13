#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

// O(nm)
void __solve() {
    int n,m,d;
    cin >> n >> m >> d;
    ll base = 0;
    vector<pair<int, int>> a(m);
    for (int i = 0; i < m; i++) {
        int x,y,t;
        cin >> x >> y >> t; x--;
        base += y;
        a[i] = {x,t};
    }

    vector<ll> dp(n);
    int las = 0;
    for (int i = 0; i < m; i++) {
        int x,t;
        tie(x,t) = a[i];
        ll R = min((t-las)*1ll*d, n-1ll); las = t;
        Slider<ll> s (dp, 2*R+1);
        for (int i = 0; i < n; i++) {
            int l = max(0ll, i-R);
            int r = min((ll)n, i+R+1);
            dp[i] = abs(x-i) + s.get_min(l, r);
        }
    }
    ll res = *min_element(dp.begin(), dp.end());
    res = base - res;
    cout << res;
}

template <typename Heap>
struct Shifter {
    using T=typename Heap::value_type;

    Heap h;
    T s=0;
    // shift all vals current in heap +x.
    void shift(T x) {
        s += x;
    }
    void push(T x) {
        h.push(x - s);
    }
    T top() {
        return h.top() + s;
    }
    void pop() {
        h.pop();
    }
};
template<class T> using MaxHeap = Shifter<priority_queue<T>>;
template<class T> using MinHeap = Shifter<priority_queue<T, vector<T>, greater<T>>>;
// slope trick
// O(m log m), a same problem, recall arc070e
void solve() {
    int n,m,d;
    cin >> n >> m >> d;
    ll base = 0;
    vector<pair<int, int>> a(m);
    for (int i = 0; i < m; i++) {
        int x,y,t;
        cin >> x >> y >> t; x--;
        base += y;
        a[i] = {x,t};
    }
    MaxHeap<ll> L;
    MinHeap<ll> R;
    L.push(a[0].first);
    R.push(a[0].first);
    ll res = 0;
    for (int i = 1; i < m; i++) {
        int z = a[i].first;
        int dt = a[i].second - a[i-1].second;
        ll radius = dt*1ll*d;
        L.shift(-radius);
        R.shift(radius);
        if (L.top() > z) {
            res += L.top() - z;
            L.push(z); L.push(z);
            R.push(L.top());
            L.pop();
        } else if (z > R.top()) {
            res += z - R.top();
            R.push(z); R.push(z);
            L.push(R.top());
            R.pop();
        } else {
            L.push(z); R.push(z);
        }
    }
    res = base - res;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
