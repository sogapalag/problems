#include <bits/stdc++.h>

using namespace std;


// another easy way, note 2n ^ 2n+1 = 1, omit.
long long f(long long x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x == 2) return 3;
    if (x == 3) return 0;
    long long h = 1ll<<(63-__builtin_clzll(x));
    long long d = x - h;
    long long res = (d&1)? 0: h;
    return res ^ f(d);
}

void solve() {
    long long a, b;
    cin >> a >> b;
    long long res = f(a) ^ f(b) ^ a;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
