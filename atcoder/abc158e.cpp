#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, p;
    cin >> n >> p;
    string s; cin >> s;

    // special case, 10^ = 0
    if (p == 2 || p == 5) {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            int x = s[i] - '0';
            if (x%p==0) {
                res += i + 1;
            }
        }
        cout << res; return;
    }

    reverse(s.begin(), s.end());
    map<int,int> mp;
    mp[0]++;
    int pw = 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i]-'0';
        sum += pw * x; // 10^k = 0, p = 2,5
        sum %= p;
        pw *= 10; pw %= p;
        mp[sum]++;
    }
    ll res = 0;
    for (auto& _: mp) {
        ll x = _.second;
        res += x*(x-1)/2;
    }
    cout << res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
