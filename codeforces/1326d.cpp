#include <bits/stdc++.h>

using namespace std;


// key: can first greedy find prefix-suffix match of s.
void solve() {
    string s; cin >> s;
    int n = s.size();
    int a = 0;
    for (; a < n/2; a++) {
        if (s[a] != s[n-a-1]) break;
    }
    int b = a;
    auto t = s.substr(a, n-2*a);
    
    n = t.size();
    if (n == 0) {
        cout << s.substr(0, a) << s.substr(s.size()-b,b) << '\n'; return;
    }
    int mx = 0; bool pref;
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l+r-i], r-i+1);
        while (0 <= i-k && i+k < n && t[i-k] == t[i+k]) {
            k++;
        }
        d1[i] = k--;
        if (i - d1[i]+1 == 0) {
            if (d1[i]*2 -1 > mx)  {
                mx = d1[i]*2 -1;
                pref = true;
            }
        }
        if (i + d1[i] == n) {
            if (d1[i]*2 -1 > mx)  {
                mx = d1[i]*2 -1;
                pref = false;
            }
        }
        if (i+k > r) {
            l = i-k;
            r = i+k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1);
        while (0 <= i-k-1 && i+k < n && t[i-k-1] == t[i+k]) {
            k++;
        }
        d2[i] = k--;
        if (i - d2[i] == 0) {
            if (2*d2[i] > mx) {
                mx = 2*d2[i];
                pref=true;
            }
        }
        if (i + d2[i] == n) {
            if (2*d2[i] > mx) {
                mx = 2*d2[i];
                pref=false;
            }
        }
        if (i+k > r) {
            l = i-k-1;
            r = i+k;
        }
    }

    cout << s.substr(0, a);
    if (pref) {
        cout << t.substr(0, mx);
    } else {
        cout << t.substr(n-mx, mx);
    }
    cout << s.substr(s.size()-b,b);
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
