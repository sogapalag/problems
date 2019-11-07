#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    string s; cin >> s;
    int n = s.size() + 1;
    vector<int> a(n);
    int len = 0;
    for (int i = 1; i < n; i++) {
        if (s[i-1] == '<') len++;
        else len = 0;
        a[i] = len;
    }
    len = 0;
    for (int i = n-2; i >= 0; i--) {
        if (s[i] == '>') len++;
        else len = 0;
        a[i] = max(a[i], len);
    }
    ll sum = 0;
    for(int x:a) sum+=x;
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
