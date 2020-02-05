#include "partial_ord_3d.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
    int n = 500;
    vector<pair<int, int>> a(n);
    const int N = 100000; 
    for (auto& x: a) {
        x = {rng(), rng()%N + 1};
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j].first < a[i].first && a[j].second < a[i].second) sum++;
        }
    }
    assert(sum == partial_ord_3d(a));
    return 0;
}
