#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pl=pair<ll,ll>;
pl& operator+=(pl& a, const pl& b){
    a.first += b.first;
    return a;
}
pl operator+(const pl& a, const pl& b){
    pl r = a;
    return r += b;
}
pl operator-(const pl& a, const pl& b){
    pl r = a;
    r.first -= b.first;
    return r;
}
template <typename Heap>
struct Shifter {
    using T=typename Heap::value_type;

    Heap h;
    T s;
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
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
void solve() {
    int n,k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    // greedy charge pontial first(time) run out
    auto ck = [&](ll po){
        MinHeap<pl> pq;
        for (int i = 0; i < n; i++) {
            pq.push({a[i]/b[i], i});
        }
        vector<ll> d(n, 0);
        for (int t = 1; t < k; t++) {
            ll x, i;
            tie(x, i) = pq.top(); pq.pop();
            if (x > k-t) break;
            d[i]++;
            x = (a[i] + d[i]*po) / b[i] - t; // watch out -/x ceil
            pq.shift({-1, 0});
            pq.push({x, i});
            if (pq.top().first < 0) return false;
        }
        return true;
    };
    ll res = bs_first<ll>(0, 2e12+100, ck);
    if (res > 2e12) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
