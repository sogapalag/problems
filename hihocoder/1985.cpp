#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    int n; cin >> n;
    ll pay = 0, cal = 0;
    ll sum = 0;
    map<int, int> mp;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        if (s[2]=='E') {
            int id, x;
            cin >> id >> x;
            mp[id] = x;
            sum += x;
        } else if (s[2] =='Y') {
            int id; cin >> id;
            pay += mp[id];
        } else {
            int id; cin >> id;
            cal += mp[id];
        }
    }
    cout << pay << ' ' << cal << ' ' << (sum-pay-cal);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
