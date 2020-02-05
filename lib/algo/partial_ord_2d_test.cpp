#include "partial_ord_2d.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
    int n = 200;
    vector<int> a(n);
    for (auto& x: a) {
        x = rng();
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) sum++;
        }
    }
    assert(sum == partial_ord_2d(a));
    return 0;
}
