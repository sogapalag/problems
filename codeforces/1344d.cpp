#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

// ef/eb = a - [(b+1)^3 - b^3]
ll delta(ll a, ll b) {
    return a - 3*b*b - 3*b - 1;
}
// note for each i, we can calc partial-diff ef/eb
//  and sum eb = 0.  => ef/eb = C, for each i
//  and d(b) is monotic on b>=0
// note we handle integer, find a closer, then adjust
void solve() {
    ll n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto& x: a) cin >> x;
    vector<ll> b(n);
    auto ck = [&](ll d){
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            // 280ms
            // note since we will adjust, we can get approx of equation quick, 3x*x=a-d-1, omit 3x
            b[i] = min(a[i], (ll)sqrt(max(0ll, (a[i]-d-1)/3)));
            // 1600ms
            //ll l = 0, r = a[i]+1;
            //while (l < r) {
            //    ll m = l + (r-l)/2;
            //    delta(a[i], m) >= d ? l = m+1 : r = m;
            //}
            //b[i] = r-1;
            // 3200ms
            //b[i] = bs_last<ll>(0, a[i]+1, [&](ll x){
            //        return delta(a[i], x) >= d;
            //        });
            sum += b[i];
            if (sum > k) return false;
        }
        return true;
        //return sum <= k;
    };
    ll d = bs_first<ll>(-4e18, 1e10, ck);
    ck(d);

    // adjust
    priority_queue<pair<ll,int>> pq;
    for (int i = 0; i < n; i++) {
        if (b[i] < a[i]) pq.emplace(delta(a[i],b[i]), i);
        k -= b[i];
    }
    while (k > 0) {
        ll d;int i;
        tie(d,i) = pq.top(); pq.pop();
        b[i]++; k--;
        if (b[i] < a[i]) pq.emplace(delta(a[i],b[i]), i);
    }
    for (auto& x: b) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
