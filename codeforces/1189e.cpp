#include <bits/stdc++.h>

using namespace std;

using ll=long long;

// realized a^4-b^4/(a-b) = k.
// but doesn't realize a^4-ka = b^4-kb.......!!
void solve() {
    int n, p, k;
    cin >> n >> p >> k;
    auto f = [&](int x) -> int{
        return ((ll)x*x%p *x%p *x%p - (ll)k * x % p + p) % p;
    };
    map<int, int> cnt;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cnt[f(x)]++;
    }
    ll res = 0;
    for (auto& kp: cnt) {
        int i = kp.second;
        res += (ll)i*(i-1)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
