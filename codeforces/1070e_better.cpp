#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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

void solve() {
    int n, m; ll T;
    cin >> n >> m >> T;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    auto d = a;
    sort(d.begin(), d.end());

    // although f*(d) not mono. but t(f) is mono. and f can greedy use lim = d(f)
    // better complexity without any DS
    auto ck = [&](int k){
        int lim = d[k-1];
        int db = (k-1)/m*m;
        int i = 0;
        ll sum = 0;
        for (int x: a)if(x<=lim){
            sum += x; i++;
            if (i <= db) sum += x;
            if (i == k) break;
        }
        return sum <= T;
    };

    int r = bs_last<int>(1, n+1, ck);
    if (r==0) cout << "0 1\n";
    else cout << r << ' ' << d[r-1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
