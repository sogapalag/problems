#include "slider.h"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
    int n = 300;
    vector<int> a(n);
    for (auto& x: a) {
        x = rng();
        x = max((int)-1e9, min(x, (int)1e9));
    }
    int d = 30;
    Slider<int> s(a, d);
    for (int i = 0; i+d <= n; i++) {
        int mi = 2e9, mx = -2e9;
        for (int j = 0; j < i+d; j++) {
            mi = min(mi, a[j]);
            mx = max(mx, a[j]);
        }
        assert(mi == s.get_min(i, i+d));
        assert(mx == s.get_max(i, i+d));
    }
    return 0;
}
