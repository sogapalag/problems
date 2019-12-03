#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll fac(int i) {
    if (i <= 1) return 1;
    return i * fac(i-1);
}
void solve() {
    ll k; cin >> k;
    vector<int> a;
    ll i = 2;
    while (k != 0) {
        a.push_back(k%i);
        k /= i; i++;
    }
    sort(a.begin(), a.end());

    int n = a.size();
    vector<int> cnt(n+1, 0);
    for(int x: a)cnt[x]++;
    ll tot = 1, p = fac(cnt[0]);
    for (int i = 0; i < n; i++) {
        int x = i+1;
        p *= fac(cnt[x]);
        cnt[x] += cnt[x-1];
        tot *= (cnt[x] - i);
    }
    tot /= p;
    
    // 0 cannot be at last pos
    if (cnt[0] > 0) {
        vector<int> cnt(n+1, 0);
        for(int x: a)cnt[x]++;
        cnt[0]--;
        ll sub = 1, p = fac(cnt[0]);
        for (int i = 0; i < n-1; i++) {
            int x = i+1;
            p *= fac(cnt[x]);
            cnt[x] += cnt[x-1];
            sub *= (cnt[x] - i);
        }
        sub /= p;
        tot -= sub;
    }
    cout << tot-1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
