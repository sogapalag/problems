#include <bits/stdc++.h>

using namespace std;


// sum is constant. and d=gcd(A) => d|sum
// then A%d,  0,..0, 2, 3, ..,24..
// least cost is left positive -1, right +1
// then some i(from right), tot = d*i
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    vector<int> d;
    for (int i = 1; i*i <= sum; i++) {
        if (sum % i == 0) {
            d.emplace_back(i);
            if (i*i < sum) {
                d.emplace_back(sum/i);
            }
        }
    }
    sort(d.begin(), d.end(), greater<int>());
    for (int x: d) {
        auto r = a;
        for (auto& y: r) {
            y %= x;
        }
        sort(r.begin(), r.end());
        vector<int> pre(n), suf(n);
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            pre[i] = tmp += r[i];
        }
        tmp = 0;
        for (int i = n-1; i >= 0; i--) {
            suf[i] = tmp += r[i];
        }
        int least = -1;
        int tot = suf[0];
        for (int i = n-1; i >= 0; i--) {
            if (tot == x*(n-i-1)) {
                least = pre[i];
                break;
            }
        }
        assert(least > -1);
        if (least <= k) {
            cout << x;
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
