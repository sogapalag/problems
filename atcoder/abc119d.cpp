#include <bits/stdc++.h>

using namespace std;


void solve() {
    int A, B, Q;
    cin >> A >> B >> Q;
    vector<long long> s(A+2);
    vector<long long> t(B+2);
    const long long INF = 1ll<<60;
    s[0] = t[0] = -INF;
    s[A+1] = t[B+1] = INF;
    for (int i = 1; i <= A; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= B; i++) {
        cin >> t[i];
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    while (Q--) {
        long long x;
        cin >> x;
        auto it = lower_bound(s.begin(), s.end(), x);
        long long sr = *it; it--;
        long long sl = *it;
        it = lower_bound(t.begin(), t.end(), x);
        long long tr = *it; it--;
        long long tl = *it;
        long long a = x - min(sl, tl);
        long long b = max(sr, tr) - x;
        long long c = sr - tl + min(sr-x, x-tl);
        long long d = tr - sl + min(tr-x, x-sl);
        long long res = min({a, b, c, d});
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
