#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

// K+X logN
// another way, add all i,j,k s.t. (i+1)(j+1)(k+1) <= k, since after must not work.
// approx ~H k.
void solve() {
    int x, y, z, k;
    cin >> x >> y >> z >> k;
    vector<long long> a(x);
    vector<long long> b(y);
    vector<long long> c(z);
    for (auto& p: a) {
        cin >> p;
    }
    for (auto& p: b) {
        cin >> p;
    }
    for (auto& p: c) {
        cin >> p;
    }
    sort(a.begin(), a.end(), greater<long long>());
    sort(b.begin(), b.end(), greater<long long>());
    sort(c.begin(), c.end(), greater<long long>());
    const long long N = 1e10+10;
    long long p = bs_last<long long>(3, N*3, [&](long long p){
            int cnt = 0;
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    for (int u = 0; u < z; u++) {
                        if (a[i]+b[j]+c[u] < p) break;
                        cnt++;
                        if (cnt >= k) return true;
                    }
                }
            }
            return false;
            });
    vector<long long> res; res.reserve(k);
    auto print = [&](){
        sort(res.begin(), res.end(), greater<long long>());
        for (auto& p: res) {
            cout << p << "\n";
        }
        exit(0);
    };
    int cnt = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int u = 0; u < z; u++) {
                long long tmp = a[i]+b[j]+c[u];
                if (tmp <= p) break; // '=' in case, =p already k, but >p must <=k. add those first
                res.emplace_back(tmp);
                cnt++;
            }
        }
    }
    for (int _ = 0; _ < k-cnt; _++) {
        res.emplace_back(p);
    }
    print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
