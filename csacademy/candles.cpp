#include <bits/stdc++.h>

using namespace std;

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
using ll=long long;
// editor's method, note optim is pick [a0,...x,x]....x
//   trick is we instead pick [a0,..]x,x..[.,x], thus a remain sorted-dec.
//     require seglazy, radd, find occur l/r
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<int>());
    vector<int> c(m);
    for (auto& x: c) {
        cin >> x;
    }

    auto ck = [&](int k){
        vector<ll> freq(n+2);//+1
        ll need = 0;
        for (int i = 0; i < k; i++) {
            if (c[i] > n) return false;
            need += c[i];
            freq[c[i]]++;
        }
        for (int i = n-1; i >= 0; i--) {
            freq[i] += freq[i+1];
        }
        ll could = 0;
        for (int i = 0; i < n; i++) {
            // sounds right, but might hard to understand.
            // let S_[k] be k set rep each night choosing. we have to ensure no same set occur in same height a[i]
            // at most a[i], trivial
            could += min((ll)a[i], freq[i+1]);
            // hard part, why unfinished can pass to after process. would some S shift collide?
            // we will prove it, imagine the choosing S is a cyclic-proc
            //   i.e. [S0,S1,...S_x-1]_{x=freq[1]} . [S0,S1,...S_y-1]_{y=freq[2]}...
            // we sats it with this order. one can see no two same S_j would occur in same a_i sats.
            //   since if that, [S_j..S_j]'s len > a_i, and a is dec. S_j can only be pushed futher, 
            //   thus by contradiction. QED
            // also by th proc, one can see at most freq[i] is trivial too.
            //   since freq[i] only inc.(from before), any add(from after) would simply collide, since it already contain all S occur after.
            if (freq[i+1] > a[i]) freq[i+2] += freq[i+1]-a[i];
        }
        return could == need;
    };
    cout << bs_last<int>(1, m+1, ck);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
