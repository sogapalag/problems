#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

// randomness can make less query
void solve() {
    int n; cin >> n;
    vector<int> odd;
    pair<int, int> res[2];
    auto row = [&](int x){
        cout << "? " << x << " 1 " << x << " " << n << endl;
        int z; cin >> z;
        if (z & 1)
            odd.emplace_back(x);
    };
    for (int i = 1; i <= n; i++) {
        row(i);
    }
    if (odd.empty()) {
        auto col = [&](int y){
            cout << "? 1 " << y << " " << n << " " << y << endl;
            int z;  cin >>z ;
            if (z & 1)
                odd.emplace_back(y);
        };
        for (int i = 1; i <= n; i++) {
            col(i);
        }
        assert(odd.size()==2);
        int y = odd[0];
        int x = bs_first<int>(1, n+1, [&](int x){
                cout << "? 1 " << y << " " << x << " " << y << endl;
                int z; cin >> z;
                return (z&1);
                });
        res[0] = {x, y};
        y = odd[1];
        res[1] = {x, y};

    } else {
        assert(odd.size()==2);
        int x = odd[0];
        int y = bs_first<int>(1, n+1, [&](int y){
                cout << "? " << x << " 1 " << x << " " << y << endl;
                int z; cin >> z;
                return (z&1);
                });
        res[0] = {x, y};
        x = odd[1];
        y = bs_first<int>(1, n+1, [&](int y){
                cout << "? " << x << " 1 " << x << " " << y << endl;
                int z; cin >> z;
                return (z&1);
                });
        res[1] = {x, y};
    }
    cout << "! " << res[0].first << " " << res[0].second << " " << res[1].first << " " << res[1].second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
